//****************************************************************************************************
//* Individual.h                                                                                     *
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

#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_

#include "genome.h"

//*********************************************************************************************************************************************
//* The structure iee was created in order to accomodate information regard a specific identifiable environment effects.                      *
//* The Individual class models an individual in the population. Its objects comprises information about the phenotypic effects, identifiable *
//* environment effects, additive genetic values, non-genetic effects and others.                                                             *
//*********************************************************************************************************************************************

namespace simulation
{
  
  class Individual
  {
  private:
    Genome genome;
    vector<double> phenVal;          // vector of phenotypic values;
    vector<double> adGenVal;         // vector of additive genetic value;
    vector<double> envDevVal;        // vector of environment deviate; 
    unsigned sireId;                 // sire id;
    unsigned damId;                  // dam id;
    unsigned indId;                  // individual id;
    char gender;                     // individual gender.
    
  public:
    inline Individual():genome(),phenVal(),adGenVal(),envDevVal(),sireId(0),damId(0),indId(0),gender('m'){};
    Individual(Parameters& p);
    Individual(Parameters& p,Individual& c,Individual& d);
    
    inline void setPhenVal(unsigned short i,double p) {phenVal[i]=p;}
    inline void setAdGenVal(unsigned short i, double a) {adGenVal[i]=a;}
    inline void setEnvDevVal(unsigned short i, double e){envDevVal[i]=e;}
    inline void setSireId(unsigned s){sireId=s;}
    inline void setDamId(unsigned d){damId=d;}
    inline void setIndId(unsigned i){indId=i;}
    inline void setGender(char g){gender=g;}
    
    inline double getPhenVal(unsigned short i)const{return phenVal[i];} 
    inline double getAdGenVal(unsigned short i)const {return adGenVal[i];}
    inline double getEnvDevVal(unsigned short i)const{return envDevVal[i];}
    inline unsigned getSireId()const{return sireId;}
    inline unsigned getDamId()const{return damId;}
    inline unsigned getIndId()const{return indId;}
    inline char getGender()const{return gender;}
        
    inline Genome& getGenome(){return genome;}

    void calcAdGenVal(Parameters& p);
    void calcPhenVal(Parameters& p);

    char pickGender();
    void zygogenesis(Parameters& p,Individual& s,Individual& d);
  };    
   

  class Individual1{
  private:
    vector<double> phenVal;          // vector of phenotypic values;
    vector<double> adGenVal;         // vector of additive genetic value;
    vector<double> envDevVal;        // vector of environment deviate; 
    vector<double> mSampling;        // mendelian sampling effect;
    unsigned sireId;                 // sire id;
    unsigned damId;                  // dam id;
    unsigned indId;                  // individual id;
    char gender;                     // individual gender.
    double inbreedingCoef;           // inbreeding coefficient calculated by tabular method.
  public:
    inline Individual1():phenVal(),adGenVal(),envDevVal(),mSampling(),sireId(0),damId(0),indId(0),gender('m'),inbreedingCoef(0){};
    Individual1(Parameters& p);
    Individual1(Parameters& p,Individual1& sire,Individual1& dam);

    inline void setInbreeding(double inbcoef){inbreedingCoef=inbcoef;}

    inline double getPhenVal(unsigned short i)const{return phenVal[i];} 
    inline double getAdGenVal(unsigned short i)const {return adGenVal[i];} 
    inline double getEnvDevVal(unsigned short i)const{return envDevVal[i];}   
    inline double getInbreedingCoef(){return inbreedingCoef;}
    inline unsigned getIndId()const{return indId;}
    inline unsigned getSireId()const{return sireId;}
    inline unsigned getDamId()const{return damId;}
    inline char getGender()const{return gender;}

    void calcAdGenVal(Parameters& p);
    void calcAdGenVal(Parameters& p,Individual1& s,Individual1& d);
    void calcPhenVal(Parameters& p);
    char pickGender();
  }; 
}


#endif
