#ifndef ERROR_CHAIN_H
#define ERROR_CHAIN_H

// a class that contains the errors 

#include <vector>
#include <iostream>

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
        //void flip(int index);
        void print();
        void initialize_random();

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

void Error_Chain::initialize_random(){

    for (int i = 0; i<error.size(); i++){
		continue;
    }

}//initialize_random;

////a single-error flip
//void Error_Chain::flip(int index){
//
//    error.at(index) *= -1;
//
//}//flip


//a print function
void Error_Chain::print(){

    cout<<error.size()<<endl;
    for (int i=0;i<error.size();i++){
        cout<<error[i]<<" ";
    }//i
    cout<<endl;

}//print

#endif
