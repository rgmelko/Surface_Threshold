#ifndef SYNDROME_H 
#define SYNDROME_H 

// a class that contains the syndrome
#define PRINT_RED(x) std::cout << "\033[1;31m" << x << "\033[0m" << " "
#define PRINT_BLUE(x) std::cout << "\033[1;34m" << x << "\033[0m" << " "
#define PRINT_GREEN(x) std::cout << "\033[1;32m" << x << "\033[0m" << " "
#define PRINT_YELLOW(x) std::cout << "\033[1;33m" << x << "\033[0m" << " "

#include <vector>
#include <iostream>

#include "error_chain.h"
#include "hypercube.h"

using namespace std;

class Syndrome
{
    public:
        int N0; //total number of zero-cells (sites)

        vector<int> syndrome;

        //public functions
        Syndrome(int N);
        void print(); //print
        void iprint(); //inverse print

		void Find_Syndrome(const Error_Chain & E, const Stars_Plaq & hcube);
};

//constructor 
//takes the total number of lattice sites
Syndrome::Syndrome(int N){

    N0 = N;

    syndrome.resize(N0,0); //assign every error as 0

}

//a print function
void Syndrome::print(){

	cout<<"Syndrome: "<<syndrome.size()<<endl;
	for (int i=0;i<syndrome.size();i++){
		if (syndrome[i] ==0)
			cout<<"("<<i<<" "<<syndrome[i]<<"), ";
		else{
			cout<<"("<<i<<" ";
			PRINT_RED(syndrome[i]);
			cout<<"), ";
		}
        //cout<<"("<<i<<" "<<syndrome[i]<<"),";
    }//i
    cout<<endl;

}//print


//only print 1s
void Syndrome::iprint(){

	cout<<"iSyndrome: "<<syndrome.size()<<endl;
	for (int i=0;i<syndrome.size();i++)
		if (syndrome[i] ==1) cout<<i<<" ";
    cout<<endl;

}//iprint


//This function takes an error configuration and find the Syndrome
//TODO: Works for 2D only
void Syndrome::Find_Syndrome(const Error_Chain & E, const Stars_Plaq & hcube){

    //reset the syndrome to all zeros
    syndrome.assign(N0,0); 

    for (int i=0;i<E.error.size();i++){
        if (E.error[i] == 1) {
            syndrome[hcube.ZeroesConnectedToOnes[i][0]] ^= 1;  //Toggle the bit
            syndrome[hcube.ZeroesConnectedToOnes[i][1]] ^= 1;  //Toggle the bit
        }
    }//i


}//Find_Syndrome

#endif
