#ifndef HYPERCUBE_H
#define HYPERCUBE_H

// hypercube.h
// a class to make a hypercubic lattice of arbitrary dimension

#define PRINT_RED(x) std::cout << "\033[1;31m" << x << "\033[0m" << " "
#define PRINT_BLUE(x) std::cout << "\033[1;34m" << x << "\033[0m" << " "
#define PRINT_GREEN(x) std::cout << "\033[1;32m" << x << "\033[0m" << " "
#define PRINT_YELLOW(x) std::cout << "\033[1;33m" << x << "\033[0m" << " "

#include <vector>
#include <iostream>

using namespace std;

class HyperCube
{
    public:
        int L_; //linear size
        int D_; //dimension
        int N_; //total number of sites

        //the lattice is a vector of vectors: no double counting
        vector<vector<int> > Neighbors; //neighbors with positive offsets
        vector<vector<int> > Negatives; //neighbors with negative offsets
        vector<vector<int> > Coordinates;

        //public functions
        HyperCube(int L, int D);
        void print();
         
    private:
        int myPow(int, int);

};

//constructor
//takes the lattice linear size L, and dimension D
HyperCube::HyperCube(int L, int D){

    L_ = L;
    D_ = D;
    N_ = myPow(L_,D_);

    //build the nearest-neighbor connections
    vector<int> temp;  //the "inner" vector
    int pair; //the bond pair index
    for (int i=0;i<N_;i++){

        temp.clear();
        for (int j=0;j<D_;j++){
            if ( ( (i+myPow(L,j))%(myPow(L,(j+1))) >= 0)  //TODO: this line not needed
                    && ( (i+myPow(L,j))%(myPow(L,(j+1))) < myPow(L,j) ) )
                pair = i+myPow(L,j) - myPow(L,(j+1));
            else
                pair = i+myPow(L,j);

            temp.push_back(pair);
        }

        Neighbors.push_back(temp);
    }//i

    //Negative neighbors
	Negatives = Neighbors;

    for (int i=0;i<N_;i++){
        temp.clear();
        for (int j=0;j<D_;j++){
            if ( ( (i+myPow(L,j))%(myPow(L,(j+1))) >= 0)  //TODO: this line not needed
                    && ( (i+myPow(L,j))%(myPow(L,(j+1))) < myPow(L,j) ) )
                pair = i+myPow(L,j) - myPow(L,(j+1));
            else
                pair = i+myPow(L,j);

            Negatives[pair][j] = i;
        }

    }//i


    //build the (x,y,z,...) coordinates of each lattice site
    temp.clear();
    temp.assign(D_,0);  //D integers with value 0

    for (int i=0;i<N_;i++){
        Coordinates.push_back(temp);

        if ( (temp[0]+1) % L_ == 0){ //end of x-row

            temp[0] = 0; //reset

            for (int j=1;j<D_;j++){
                if ( (temp[j]+1) % L_ == 0)
                    temp[j] = 0; //reset
                else{
                    temp[j]++;
                    break;
                }
            }//j
        }//if
        else
            temp[0]++;
    }


}//constructor

//a print function
void HyperCube::print(){

    cout<<"L D N \n";
    cout<<L_<<" "<<D_<<" "<<N_<<endl;

    cout<<"Neighbor list:"<<endl;
    for (int i=0;i<Neighbors.size();i++){
        cout<<i<<" ";
        for (int j=0;j<Neighbors[i].size();j++){
            PRINT_RED(Neighbors[i][j]);
        }
        cout<<endl;
    }//i

    cout<<"Negative Neighbor list:"<<endl;
    for (int i=0;i<Negatives.size();i++){
        cout<<i<<" ";
        for (int j=0;j<Negatives[i].size();j++){
            PRINT_GREEN(Negatives[i][j]);
        }
        cout<<endl;
    }//i

//    cout<<"Coordinates:"<<endl;
//    for (int i=0;i<Coordinates.size();i++){
//        cout<<i<<" ";
//        for (int j=0;j<Coordinates[i].size();j++){
//            //cout<<j<<" ";
//            //cout<<Coordinates[i][j]<<" ";
//			PRINT_YELLOW(Coordinates[i][j]);
//
//        }
//        cout<<endl;
//    }//i
//
}

//a simple function to calculate powers of an integer: not for general use
int HyperCube::myPow (int x, int p) {
  int i = 1;
  for (int j = 1; j <= p; j++)  i *= x;
  return i;
}


//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//This is a DERIVED CLASS which contains the data structures specific for the Toric Code
typedef boost::multi_array<int, 1> array_1t;
typedef boost::multi_array<int, 2> array_2t;
class Stars_Plaq : public HyperCube
{
    public:
	    int N0;   //number of zero cells
        int N1;   //number of DEGREES OF FREEDOM
        int N2;   //number of 2 cells

		//see generalD_1_2.code.h :  https://github.com/rgmelko/Ising_Hypercube/tree/v1.0
        vector<vector<int> > Plaquette;

        Stars_Plaq(int L, int D); //constructor

        //All of the 2-cells which are attached to a given 1-cell
        vector<vector<int> > TwosConnectedToOnes; 
        //The 1 cells connected to each 0 cell: for the gauge cluster flip
        array_2t OnesConnectedToZero;
        //conversely, two zero-cells connected by each 1-cell (bond)
        array_2t ZeroesConnectedToOnes;

        void prints();


};

Stars_Plaq::Stars_Plaq(int L, int D):HyperCube(L,D) {
    
	N0 = N_;  
	N1 = D*N_;  
	//cout<<N0<<" "<<N1<<endl;

    //use it to built the sigma-z plaquettes
    vector <int> temp;
    temp.assign(4,0);  //assign 4 zeros to this vector

    //ANN's IDEA JUST SO YOU KNOW
    //Input: plaquette#
    //Output: the 4 1-cells associated with that plaquette
    for (int v=0; v<N0; v++ ){ //loop over 0-cells

        for (int i=0; i<(D_-1); i++){ //loop that defines all 2-cells per vertex
            for (int j=0; j<D_; j++){

                if (i<j){  // cout<<i<<" "<<j<<endl;

                    temp[0] = D_*v+i;
                    temp[1] = D_*v+j;
                    temp[2] = D_*Neighbors[v][i]+j;
                    temp[3] = D_*Neighbors[v][j]+i;
                    Plaquette.push_back(temp);

                }//if

            }//j
        }//i

    }//v

    N2 = Plaquette.size(); //number of 2 cells
	//cout<<N2<<endl;

    //DEBUG: check if Plaquette has any errors
    //vector<int> Check(Plaquette.size(),0);
    vector<int> Check(N1,0);
    //cout<<"Check size : "<<Check.size()<<endl;
    for (int j=0; j<Plaquette.size(); j++)
        for (int k=0; k<Plaquette[j].size(); k++)
            Check[Plaquette[j][k]]++;

    for (int j=0; j<Check.size(); j++){
        if (Check[j] != 2*(D_-1)){ 
            cout<<"Plaquette error \n";
            cout<<j<<" "<<Check[j]<<endl;
        }   
    }

    //Now, make the data structure used to relate the DOF to the 4 plaquettes
    TwosConnectedToOnes.resize(N1);
    for (int i=0; i<Plaquette.size(); i++)
        for (int j=0; j<Plaquette[i].size(); j++)
            TwosConnectedToOnes[Plaquette[i][j]].push_back(i);

    //The one cells connected to each zero-cell.  Used for cluster updates
	OnesConnectedToZero.resize(boost::extents[N0][2*D_]); 
    int back_site;
	for (int n=0; n<N0; n++)
		for (int d=0; d<D_; d++){
            OnesConnectedToZero[n][d] = D_*n + d;
            back_site = Negatives[n][d];
            OnesConnectedToZero[n][d+D_] = D_*back_site + d;
        }

    //TODO: DEBUG - only works for 2D
    //The zero cells connected to each one-cell.  Used to define the syndrome
    // - inverse of OnesConnectedToZero
    if (D_ != 2)
        PRINT_RED("WARNING - ZeroesConnectedToOnes works for 2D only");
	ZeroesConnectedToOnes.resize(boost::extents[N1][2]);  //Two sites touch each bond
    int site0; int site1;
    for (int n=0; n<N1; n++){
        site0 = n/D_;
        ZeroesConnectedToOnes[n][0] = site0;
        if (n%2 == 0) site1 = Neighbors[site0][0];
        else site1 = Neighbors[site0][1];
        ZeroesConnectedToOnes[n][1] = site1;
    }//n

	
}; //constructor

void Stars_Plaq::prints(){

    cout<<L_<<" "<<D_<<" "<<N1<<" "<<N2<<endl;

    cout<<"Plaquette \n";
    for (int i=0; i<Plaquette.size(); i++){
        PRINT_RED(i);
        for (int j=0; j<4; j++)
            //cout<<Plaquette[i][j]<<" ";
            PRINT_RED(Plaquette[i][j]);
        cout<<endl;
    }//i

    for (int i=0; i<TwosConnectedToOnes.size(); i++){
        PRINT_GREEN(i);
        for (int j=0; j<TwosConnectedToOnes[i].size(); j++)
            //cout<<TwosConnectedToOnes[i][j]<<" ";
            PRINT_GREEN(TwosConnectedToOnes[i][j]);
        cout<<endl;
    }

    for (int i=0; i<OnesConnectedToZero.size(); i++){
        PRINT_BLUE(i);
        for (int j=0; j<OnesConnectedToZero[i].size(); j++){
            cout<<OnesConnectedToZero[i][j]<<" ";
        }
        cout<<endl;
    }

    for (int i=0; i<ZeroesConnectedToOnes.size(); i++){
        PRINT_YELLOW(i);
        for (int j=0; j<ZeroesConnectedToOnes[i].size(); j++){
            cout<<ZeroesConnectedToOnes[i][j]<<" ";
        }
        cout<<endl;
    }


}//print

#endif