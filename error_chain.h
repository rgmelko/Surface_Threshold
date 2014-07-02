#ifndef ERROR_CHAIN_H
#define ERROR_CHAIN_H

// a class that contains the error chain

#define PRINT_RED(x) std::cout << "\033[1;31m" << x << "\033[0m" << " "
#define PRINT_BLUE(x) std::cout << "\033[1;34m" << x << "\033[0m" << " "
#define PRINT_GREEN(x) std::cout << "\033[1;32m" << x << "\033[0m" << " "
#define PRINT_YELLOW(x) std::cout << "\033[1;33m" << x << "\033[0m" << " "

#include <vector>
#include <iostream>

#include <boost/random.hpp>
boost::random::mt19937 egen; //Global random number generator for this class
double rnd_real01(){  //real # including 0 and excluding 1
    boost::random::uniform_real_distribution <> coin(0, 1); 
    return coin(egen); }
int ernd_int(int a, int b){ //an integer betwenn (and including a and b)
    boost::random::uniform_int_distribution <> dist(a, b);
    return dist(gen); }

using namespace std;

class Error_Chain
{
	private:
		//void flip(const int & index);
        int N1; //total number of one-cells (edges)

		//The weight of an error p/(1-p)
		double W_E;

    public:

        vector<int> error;

        //public functions
        Error_Chain(int N);
        Error_Chain();
        void resize(int N);
        void print();
        void iprint();
        void initialize_random(const double p, const int seed);

		void GaugeUpdateX(const Stars_Plaq & hcube, const int & );
		void GaugeUpdateZ(const Stars_Plaq & hcube, const int & );

		void MetropolisUpdate(const Stars_Plaq & hcube);

};

//constructor 1
Error_Chain::Error_Chain(){

    error.clear(); 

}

//constructor 2
//takes the total number of lattice sites
Error_Chain::Error_Chain(int N){

    N1 = N;

    error.resize(N1,0); //assign every error as 0

}

//takes the total number of lattice sites
void Error_Chain::resize(int N){

    N1 = N;

    error.resize(N1,0); //assign every error as 0

}

//This function initializes the random error configuration, given
//a probability for error p, and a seed
void Error_Chain::initialize_random(const double p, const int seed){

    egen.seed(seed);

    for (int i = 0; i<error.size(); i++){
        if (rnd_real01() < p) error[i] = 1;
		else error[i] = 0;
    }

	W_E = p/(1.0-p);  //This is the weight for a single error of probability p

}//initialize_random;


//This function modifies the error chain by performing an XXXX vertex operation
void Error_Chain::GaugeUpdateX(const Stars_Plaq & hcube, const int & vertex){

	for (int i=0; i<hcube.OnesConnectedToZero[vertex].size(); i++)
		error[hcube.OnesConnectedToZero[vertex][i]] ^= 1;  //XXXX error flip


}//GaugeUpdateX


//This function modifies the error chain by performing an ZZZZ plaquette operation
void Error_Chain::GaugeUpdateZ(const Stars_Plaq & hcube, const int & vertex){

	for (int i=0; i<4; i++)  // Does a plaquette always have 4 DOFs?
		error[hcube.Plaquette[vertex][i]] ^= 1;  //ZZZZ error flip


}//GaugeUpdateZ


//----------------------------------------------------------------------------------
//this function performs a metropolis update of the error pattern using Guage Updates,
//thus retaining the same syndrome as the original E chain
void Error_Chain::MetropolisUpdate(const Stars_Plaq & hcube){

	int rplaq; //random plaquette
	int N_E; //number of errors on that plaquette
	double Met_weight, rand_num;

	for (int count=0; count<hcube.N2; count++){

        //choose a random plaquette
		rplaq= ernd_int(0,hcube.N2-1); 
		if (rplaq >= hcube.N2) cout<<"Check Metrop: "<<rplaq<<" ";

        N_E = 0;
		for (int i=0; i<4; i++)  
			N_E += error[hcube.Plaquette[rplaq][i]];  //ZZZZ error flip
		//cout<<rplaq<<" N_E "<<N_E<<endl;

		Met_weight = pow(W_E,4.0-2.0*N_E);  //here lies the Metropolis condition: fix this pow
		//PRINT_BLUE(Met_weight);

		if (Met_weight < 1){ //need to do the metropolis test
			rand_num = rnd_real01();
			if (Met_weight > rand_num ){//accept
				GaugeUpdateZ(hcube,rplaq);
				//cout<<rplaq<<" "<<Met_weight<<" "<<rand_num<<endl;
			}
			//else reject and do nothing
			//else cout<<rplaq<<" reject "<<Met_weight<<" "<<rand_num<<endl;
		}
		else{ //if the weight is greater than or equal to unity
			//PRINT_BLUE(Met_weight);
			GaugeUpdateZ(hcube,rplaq); //flip the plaquette
		}

	}//count
	//cout<<endl;

}//------------------------------------------------------------------MetropolisUpdate


//a print function
void Error_Chain::print(){

    cout<<"E-Chain: "<<error.size()<<endl;
	for (int i=0;i<error.size();i++){
		if (error[i] ==0)
			cout<<"("<<i<<" "<<error[i]<<"), ";
		else{
			cout<<"("<<i<<" ";
			PRINT_BLUE(error[i]);
			cout<<"), ";
		}
    }//i
    cout<<endl;

}//print

//an inverse print function
void Error_Chain::iprint(){

    cout<<"E-chain: "<<error.size()<<endl;
	for (int i=0;i<error.size();i++)
		if (error[i] == 1) cout<<i<<" ";
    cout<<endl;

}//iprint


#endif
