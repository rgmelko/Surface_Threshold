#ifndef SYNDROME_H 
#define SYNDROME_H 

// a class that contains the syndrome

#include <vector>
#include <iostream>

using namespace std;

class Syndrome
{
    public:
        int N0; //total number of zero-cells (sites)

        vector<int> syndrome;

        //public functions
        Syndrome(int N);
        void print();

};

//constructor 
//takes the total number of lattice sites
Syndrome::Syndrome(int N){

    N0 = N;

    syndrome.resize(N0,0); //assign every error as 0

}

//a print function
void Syndrome::print(){

    cout<<syndrome.size()<<endl;
    for (int i=0;i<syndrome.size();i++){
        cout<<syndrome[i]<<" ";
    }//i
    cout<<endl;

}//print

#endif
