#include <iostream>
#include <vector>
using namespace std;

// Requires BOOST: http://www.boost.org
// compile example:  g++ Two_D_Syndrome.cpp -I /opt/local/include/

#include <boost/multi_array.hpp>


//-----GLOBAL RANDOM NUMBER GENERATOR
#include <boost/random.hpp>
boost::random::mt19937 gen; //instantize a random numbrer generator
boost::random::uniform_real_distribution <> metrop(0, 1); //real # including 0 and excluding 1
//Random interger between (and including a and b)
int rnd_int(int a, int b)
{ boost::random::uniform_int_distribution <> dist(a, b);
  return dist(gen); }

//----main
int main ( int argc, char *argv[] )
{

    for (int i=0; i<1000; i++){
       cout<<rnd_int(23,25)<<" ";
       cout<<metrop(gen)<<endl;
    }

   return 0;
}

