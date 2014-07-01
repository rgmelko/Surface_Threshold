#ifndef MEASURE_H
#define MEASURE_H

// measure.h: a class that performs statistical measurements of estimators
// modelled after https://github.com/rgmelko/Ising_Hypercube/releases

#include <fstream>

#include "error_chain.h"
#include "hypercube.h"

typedef boost::multi_array<int, 2> array_2t;

class Measure
{
    private:
       int MCS;
       char fname[8]; //we do it so that every object has its own filename
       void createName(char *name, const int &);

    public:
      double TOT_energy;   //energy

      Measure(const int & SimNum, const int & mcs);
      void zero();
      void output();

	  //various measurement schemes
	  void Energy_0_Lby2_ZZZZ(const Error_Chain & E, const Stars_Plaq & hcube);
 
};

//constructor
Measure::Measure(const int & SimNum, const int & mcs){

    MCS = mcs; //# of Monte Carlo steps

    TOT_energy = 0.0;

    createName(fname, SimNum); //create the first two characters of the file name
    fname[2] = '.';
    fname[3] = 'd';
    fname[4] = 'a';
    fname[5] = 't';
    fname[6] = 'a';
    fname[7] = '\0';
}

//zero
void Measure::zero(){

    TOT_energy = 0.0;

}


//Let's measure a simple energy correlation function between the (0,0) plaquette
//and the (L/2,L/2) plaquette
void Measure::Energy_0_Lby2_ZZZZ(const Error_Chain & E, const Stars_Plaq & hcube){

	double E0, EL2;

	int plaq = 0; //the zeroth plaquette to start
	E0 = 1;
	for (int i=0; i<4; i++)  // see GaugeUpdateZ
		E0 *= 2*(E.error[hcube.Plaquette[plaq][i]]) - 1; //modify to +1 and -1   

    //Now the (L/2,L/2) plaquette
	int lx = hcube.L_/2; int ly = hcube.L_/2;
	plaq = ly*hcube.L_ + lx;
	//cout<<"Plaq "<<plaq<<endl;

	EL2 = 1;
	for (int i=0; i<4; i++)  // see GaugeUpdateZ
		EL2 *= 2*(E.error[hcube.Plaquette[plaq][i]]) - 1; //modify to +1 and -1  

    TOT_energy += E0 * EL2;

}//update


void Measure::output(){

    ofstream cfout;
    cfout.open(fname,ios::app); //fname created in constructor

    int T=0;
    cfout<<T<<" ";
    cfout<<TOT_energy/(1.0*MCS)<<endl;

    cfout.close();

}//output


//a private function to create the first two characters of the integer file name
void Measure::createName(char *fname, const int & num){

    int SimTemp = num;

    if (SimTemp/10 == 0)
        fname[0]='0';
    else if (SimTemp/20 == 0) {
        fname[0]='1';
        SimTemp = SimTemp - 10;   }
    else if (SimTemp/30 == 0) {
        fname[0]='2';
        SimTemp = SimTemp - 20;   }
    else if (SimTemp/40 == 0) {
        fname[0]='3';
        SimTemp = SimTemp - 30;   }
    else if (SimTemp/50 == 0) {
        fname[0]='4';
        SimTemp = SimTemp - 40;   }
    else if (SimTemp/60 == 0) {
        fname[0]='5';
        SimTemp = SimTemp - 50;   }
    else if (SimTemp/70 == 0) {
        fname[0]='6';
        SimTemp = SimTemp - 60;   }
    else if (SimTemp/80 == 0) {
        fname[0]='7';
        SimTemp = SimTemp - 70;   }
    else if (SimTemp/90 == 0) {
        fname[0]='8';
        SimTemp = SimTemp - 80;   }
    else if (SimTemp/100 == 0) {
        fname[0]='9';
        SimTemp = SimTemp - 90;   }

    if (SimTemp == 0) fname[1] = '0';
    else if (SimTemp%9 == 0) fname[1] = '9';
    else if (SimTemp%8 == 0) fname[1] = '8';
    else if (SimTemp%7 == 0) fname[1] = '7';
    else if (SimTemp%6 == 0) fname[1] = '6';
    else if (SimTemp%5 == 0) fname[1] = '5';
    else if (SimTemp%4 == 0) fname[1] = '4';
    else if (SimTemp%3 == 0) fname[1] = '3';
    else if (SimTemp%2 == 0) fname[1] = '2';
    else if (SimTemp%1 == 0) fname[1] = '1';

}//createName

#endif
