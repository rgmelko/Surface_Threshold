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
    return coin(egen);
}

using namespace std;

class Error_Chain
{
	private:
		//void flip(const int & index);

    public:
        int N1; //total number of one-cells (edges)

        vector<int> error;

        //public functions
        Error_Chain(int N);
        Error_Chain();
        void resize(int N);
        void print();
        void iprint();
        void initialize_random(const double p, const int seed);

		void GaugeUpdateX(const Stars_Plaq & hcube, const int & link);
		void GaugeUpdateZ(const Stars_Plaq & hcube, const int & link);

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
    }

}//initialize_random;


//This function modifies the error chain by performing an XXXX vertex operation
void Error_Chain::GaugeUpdateX(const Stars_Plaq & hcube, const int & link){

	if (link >= N1){
		PRINT_RED("GaugeUpdateX out of bounds");
		return;
	}

	for (int i=0; i<hcube.OnesConnectedToZero[link].size(); i++)
		error[hcube.OnesConnectedToZero[link][i]] ^= 1;  //XXXX error flip


}//GaugeUpdateX


//This function modifies the error chain by performing an ZZZZ plaquette operation
void Error_Chain::GaugeUpdateZ(const Stars_Plaq & hcube, const int & link){

	if (link >= N1){
		PRINT_RED("GaugeUpdateZ out of bounds");
		return;
	}

	for (int i=0; i<4; i++)  // Does a plaquette always have 4 DOFs?
		error[hcube.Plaquette[link][i]] ^= 1;  //ZZZZ error flip


}//GaugeUpdateX


//a print function
void Error_Chain::print(){

    cout<<"Error: "<<error.size()<<endl;
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

    cout<<"iError: "<<error.size()<<endl;
	for (int i=0;i<error.size();i++)
		if (error[i] == 1) cout<<i<<" ";
    cout<<endl;

}//iprint


#endif
