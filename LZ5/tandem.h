//****************************************************************************************************
//* tandem.h                                                                                         *
//*                                                                                                  *
//* Copyright (c) 2008 LuCCA-Z (Laboratório de Computação Científica Aplicada à Zootecnia),          *
//* Rodovia Comandante João Ribeiro de Barros (SP 294), km 651. UNESP,                               *
//* Dracena, São Paulo, Brazil, 17900-000                                                            *
//*                                                                                                  *
//* This file is part of LZ5.                                                                        *
//*                                                                                                  *
//* LZ5 is free software: you can redistribute it and/or modify it under the terms of the            *
//* GNU General Public License as published by the Free Software Foundation, either version 3        *
//* of the License, or (at your option) any later version.                                           *
//*                                                                                                  *
//* LZ5 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without         *
//* even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See            *
//* the GNU General Public License for more details. You should have received a copy of the          *
//* GNU General Public License along with LZ5. If not, see <http://www.gnu.org/licenses/>.           *
//*                                                                                                  *
//* Acknowledgements                                                                                 *
//*                                                                                                  *
//* To Dr. Rohan L. Fernando from Iowa State University and Dr. Ricardo Frederico Euclydes           *
//* from Vicosa Federal University, who had great influence in ideas behind the LZ5's development.   *
//*                                                                                                  *
//****************************************************************************************************
#ifndef __TANDEM_H_
#define __TANDEM_H_
#include <vector>
#include <map>
#include "population.h"
#include "parameters.h"
#include "sel.h"
#include "specStructures.h"

using std::vector;

namespace selection{

class Tandem:public Sel{
 private:
	string name;
	std::map<double,pair<double> > evcc;                      //key= economic values; mapped value= pair structure (a=trait id and b=changing criteria)
	vector<vector<double> > trait_means;
	vector<double> heritability;
	vector<double> trait_corr;
	vector<double> GGP;
	vector<vector<double> > GGR;                             //rows are associated with generations and columns are associated with traits
	std::map<unsigned short,unsigned short> NumGenSel;            //key = trait id; mapped value= number of generations under selection
	unsigned int cr_troca;

 public:
  inline Tandem():Sel(),name(),evcc(), trait_means(),heritability(), trait_corr(), GGP(), GGR(), NumGenSel(), cr_troca(1){};

  void tandemSel(simulation::Population& pop,unsigned long selm,unsigned long self,char sc,bool rev,unsigned short ng,simulation::Parameters& p,char mating,int noff);

  vector<double> calcGGP(double i, vector<double> h, vector<double> dp, vector<vector<double> > r);
  vector<double> calcGGR(vector<double>& mean0,vector<double>& mean1);
  double calcTEV(int g);                                                                                   //i indicates the generation. If i=-1, the total economic values for all traits and all generations are calculated

  inline string getName(){return name;}
  inline size_t getNumGen()const{return GGR.size();}
  inline size_t getNumTraits()const{return evcc.size();}
  inline double getRGG(int i,int j)const{return GGR[j][i];}                                                //j is the generation id  and i is the trait id.
  inline double getMeans(int i,int j)const{return trait_means[j][i];}                                      //j is the generation id  and i is the trait id.
  inline unsigned short getNumGenSel(unsigned short trait)const{return NumGenSel.find(trait)->second;}
  vector<unsigned short> getSelOrder()const;

  inline void setName(string n){name=n;}
  void setEvcc(simulation::Parameters& p);

  void exec(lz5::lz5_Result_Struct& e,simulation::Parameters& p,simulation::Population& pop);
};
}
#endif  

// TODO: Criar construtor padrão para a classe Tandem que recebe parameters como argumento.
