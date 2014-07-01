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

#include "hypercube.h"
#include "syndrome.h"
#include "error_chain.h"


//----main
int main ( int argc, char *argv[] )
{

   Stars_Plaq square(6,2); //2D lattice with L linear dimension
   //square.print();
   //square.prints();

   Error_Chain E(2*square.N_); //The error E
   E.initialize_random(0.51,345450);
   E.iprint();

   Syndrome S(square.N_);
   S.Find_Syndrome(E,square);
   S.iprint();

   E.MetropolisUpdate(square);
   E.iprint();
   S.Find_Syndrome(E,square);
   S.iprint();

   return 0;
}

