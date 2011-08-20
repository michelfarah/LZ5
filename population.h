//****************************************************************************************************
//* population.h                                                                                     *
//*                                                                                                  *
//* Copyright (c) 2008 LuCCA-Z (Laboratório de Computação Científica Aplicada à Zootecnia),     *
//* Rodovia Comandante João Ribeiro de Barros (SP 294), km 651. UNESP,                              *
//* Dracena, São Paulo, Brazil, 17900-000                                                           *
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

#ifndef __POPULATION_H__
#define __POPULATION_H__


#include "individual.h"
#include "specStructures.h"
#include "Lz5_Interpreter.h"


//* *******************************************************************************************************************************************
//* Population class is the base of whole simulation class. Calculations realized by one object determines several aspects of the simulation  *
//* round.                                                                                                                                    *
//*********************************************************************************************************************************************
namespace simulation{

  class findQtl{
  public:
    inline bool operator()(const Locus& a){return (a.getType()=='q');}             //function to find a qtl within the genome. Used to generate disequilibrium between a Qtl and one or two marker(s)
  };

  class findMarker{
  public:
    inline bool operator()(const Locus& a){return (a.getType()=='m');}             //function to find a marker within the genome. Used to generate disequilibrium between a Qtl and one or two marker(s)
  };
  
  class Population
  {
  private:    
    vector<vector<Individual> > pop;                                               //Matrix whose rows correspond to generation an columns to individuals; The first vector(rows) is always the base-population, the second is generation 0, the third is generation 1 and so on.
    vector<Individual*> selMales;                                                        
    vector<Individual*> selFem;                                                         
    string name;
    
  public:
    inline Population():pop(),selMales(),selFem(),name(){};
    inline Population(Parameters& p):pop(),selMales(p.getNumMale()),selFem(p.getNumFem()),name(){};

    inline void setName(string n){name=n;}
    inline void setSelMales(vector<Individual*> sMales){selMales=sMales;}
    inline void setSelFem(vector<Individual*> sFem){selFem=sFem;}

    inline string getName()const {return name;}
    inline vector<vector<Individual> >& getPop(){return pop;}
    inline vector<vector<Individual> >::iterator begin(){return pop.begin();}
    inline vector<vector<Individual> >::iterator end(){return pop.end();}
    inline size_t getNumGeneration(){return pop.size();}

    void createBasePop(Parameters& p,unsigned int size);  

    vector<double>& calcAdVar(vector<double>& var);
    vector<double>& calcGenAdVar(vector<double>& var,unsigned short i);
    vector<double>& calcGenPhenVar(vector<double>& var,unsigned short i);
    vector<double>& calcGenEnvDevVar(vector<double>& evar,unsigned short i);
    vector<double>& calcGrandMean(vector<double>& var);
    vector<double>& calcGenMean(vector<double>& var,unsigned short i);
    vector<double>& calcGenAlelleFreq(vector<double>& afreq,unsigned short i);
    void calcAdCor();
    unsigned long totalSize();

    void createGen(Parameters& p,char mating,unsigned int numoff);                  // The argument mating defines what type of mating system will be used to generate the offspring. The letters p, n or r are used to refer to positive assortative mating, negative assortative mating and random mating respectively. The argument numoff defines the number of products (offspring) generated per mating.
    
    void generateDiseq(Parameters& p);

    void exec(lz5::lz5_Result_Struct& e,Parameters& p);    
  };


  class Population1
  {
  private:    
    vector<vector<Individual1> > pop;                                              //Matrix whose rows correspond to generation an columns to individuals; The first vector(rows) is always the base-population, the second is generation 0, the third is generation 1 and so on.
    vector<Individual1*> selMales;                                                        
    vector<Individual1*> selFem;
    vector<vector<double> > relTable;                                              //Relationship table produced by the tabular method.
    string name;
    
  public:
    inline Population1():pop(),selMales(),selFem(),relTable(),name(){};
    inline Population1(Parameters& p):pop(),selMales(p.getNumMale()),selFem(p.getNumFem()),relTable(),name(){};

    inline void setName(string n){name=n;}
    inline void setSelMales(vector<Individual1*> sMales){selMales=sMales;}
    inline void setSelFem(vector<Individual1*> sFem){selFem=sFem;}

    inline string getName()const {return name;}
    inline vector<vector<Individual1> >& getPop(){return pop;}
    inline size_t getNumGeneration(){return pop.size();}

    void createBasePop(Parameters& p,unsigned int size);  

    vector<double>& calcAdVar(vector<double>& var);
    vector<double>& calcGenAdVar(vector<double>& var,unsigned short i);
    vector<double>& calcGenPhenVar(vector<double>& var,unsigned short i);
    vector<double>& calcGenEnvDevVar(vector<double>& evar,unsigned short i);
    vector<double>& calcGrandMean(vector<double>& mean);
    vector<double>& calcGenMean(vector<double>& mean,unsigned short i);
    void calcAdCor();
    unsigned long totalSize();
    void tabularMethod(unsigned gnumber);                                           //Calculate inbreeding coefficients and assign them to individuals;


    void createGen(Parameters& p,char mating,unsigned int numoff);                  // The argument mating defines what type of mating system will be used to generate the offspring. The letters p, n or r are used to refer to positive assortative mating, negative assortative mating and random mating respectively. The argument numoff defines the number of products (offspring) generated per mating.
    
    void generateDiseq(Parameters& p);

    void exec(lz5::lz5_Result_Struct& e,Parameters& p);    
  };
}

#endif
