#ifndef ERROR_CHAIN_H
#define ERROR_CHAIN_H

// a class that contains the errors 

#include <vector>
#include <iostream>

#include <boost/random.hpp>
boost::random::mt19937 egen; //Global random number generator for this class
double rnd_coin(){  //real # including 0 and excluding 1
    boost::random::uniform_real_distribution <> coin(0, 1); 
    return coin(egen);
}
int rnd_edge(int a, int b) { 
    boost::random::uniform_int_distribution <> dist(a, b);
    return dist(egen); 
}

using namespace std;

class Error_Chain
{
    public:
        int N1; //total number of one-cells (edges)

        //the lattice is a vector of vectors: no double counting
        vector<int> error;

        //public functions
        Error_Chain(int N);
        Error_Chain();
        void resize(int N);
        void print();
        void initialize_random(const double p, const int seed);

};

//constructor 1
//takes the total number of lattice sites
Error_Chain::Error_Chain(){

    error.clear(); 

}

//constructor 2
//takes the total number of lattice sites
Error_Chain::Error_Chain(int N){

    N1 = N;

    error.resize(N1,0); //assign every error as 1

}

//takes the total number of lattice sites
void Error_Chain::resize(int N){

    N1 = N;

    error.resize(N1,0); //assign every error as 1

}

//This function initializes the random error configuration, given
//a probability for error p, and a seed
void Error_Chain::initialize_random(const double p, const int seed){

    egen.seed(seed);

    for (int i = 0; i<error.size(); i++){
        if (rnd_coin() < p) error[i] = 1;
    }

}//initialize_random;


//a print function
void Error_Chain::print(){

    cout<<error.size()<<endl;
    for (int i=0;i<error.size();i++){
        cout<<error[i]<<" ";
    }//i
    cout<<endl;

}//print

#endif
