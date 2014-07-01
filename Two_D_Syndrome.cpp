#include <iostream>
#include <vector>
using namespace std;

// Requires BOOST: http://www.boost.org
// compile example:  g++ Two_D_Syndrome.cpp -I /opt/local/include/

#include <boost/multi_array.hpp>

//-----GLOBAL RANDOM NUMBER GENERATOR
#include <boost/random.hpp>
boost::random::mt19937 gen; //instantize a random numbrer generator
//boost::random::uniform_real_distribution <> metrop(0, 1); //real # including 0 and excluding 1
//Random interger between (and including a and b)
int rnd_int(int a, int b)
{ boost::random::uniform_int_distribution <> dist(a, b);
  return dist(gen); }
//-----------------------------------

#include "simparam.h"
#include "hypercube.h"
#include "syndrome.h"
#include "error_chain.h"
#include "measure.h"


//----main
int main ( int argc, char *argv[] )
{

   PARAMS param; //read in parameter file
   param.print();

   Stars_Plaq square(param.nX_,param.Dim_); //2D lattice with L linear dimension
   //square.print();
   //square.prints();

   Error_Chain E(2*square.N_); //The error E
   E.initialize_random(param.P_,param.SEED_);
   //E.iprint();

   Syndrome S(square.N_);
   S.Find_Syndrome(E,square);
   S.iprint();

   Measure estimators(0,param.MCS_);


   //for (int k=0; k<param.nBin_; k++){  //loop over bins

   double probP;
   for (int p=0; p<100; p++){    //loop over P
	   probP = (1.*p)/(100.);
	   E.initialize_random(probP,param.SEED_);

	   for (int i=0; i<param.EQL_; i++) //equilibrate
		   E.MetropolisUpdate(square);

	   estimators.zero();
	   for (int i=0; i<param.MCS_; i++){ 
		   E.MetropolisUpdate(square);
		   estimators.Energy_0_Lby2_ZZZZ(E,square);
	   }//i
	   estimators.output(probP);

   }//k or p

   S.Find_Syndrome(E,square);
   S.iprint();

   return 0;
}

