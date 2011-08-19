//****************************************************************************************************
//* locus.h                                                                                          *
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

#ifndef _LOCUS_H_
#define _LOCUS_H_

//*********************************************************************************************************************************************
//* The class locus define the model that should be used by the simulator when creating the individual's genome (or chromosomes).             *
//* It is assumed that all alelles of the same type, say A1 and A2, has the same frequency and the same average effect among all poligenic lo *
//* ci. Thus all poligenic loci have the same set of genotypic effect as well. Qtls have their effects defined individually.                  * 
//*********************************************************************************************************************************************

#include "parameters.h"
#include <iostream>
#include <gsl/gsl_rng.h>
using std::vector;

extern gsl_rng* prand;

namespace simulation
{
  
  class Locus
  {
  private:
    vector<unsigned short> alellesConfig;                                                                    //Alelles configuration. The first position in the vector is regard to the paternal alelle and the second position to the maternal alelle. The alelles are coded as 0 or 1.
    vector<double> locusEffect;
    unsigned short traitId;
    double locusPos;
    char type;    
    
  public:
    inline Locus():alellesConfig(),locusEffect(),traitId(),locusPos(0),type('m'){};
    Locus(Parameters& p,unsigned short cId);                                                                //cId is the id of the chromosome in which the locus is located.
    Locus(Parameters& p,unsigned short tId,unsigned short qId,unsigned short cId);                          //tId is the trait for which the Qtl has effects; qId is the Qtl id within the trait.
    Locus(Parameters& p,unsigned long mId,double dist);                                                     //the argument nmark is the number of marker in the chromosome for which this marker will be created and initialized.
    
    inline void setLocusEffect(unsigned short i,double e){locusEffect[i]=e;}
    void setLocusEffect(Parameters& p);
    void setQtlLocusEffect(Parameters& p,unsigned short i,unsigned short j);
    inline void setAlellesConfig(unsigned short i,unsigned short j,unsigned short k,unsigned short l){alellesConfig[i]=k;alellesConfig[j]=l;}    
    void setAlellesConfig(Parameters& p);
    void setAlellesConfig(Parameters& p,unsigned short a,unsigned short qId);
    void setAlellesConfig();    
    inline void setTraitId(unsigned short t){traitId=t;}
    void setTraitId(Parameters& p,unsigned lc);
    inline void setLocusPos(double p){locusPos=p;}
    inline void setPos(Parameters& p,unsigned short cId){locusPos=gsl_rng_uniform(prand)*p.getChromSizes(cId);}
    inline void setPos(unsigned long mid,double dist){locusPos=double(mid)*dist;}
    inline unsigned short getAlellesConfig(unsigned short i)const{return alellesConfig[i];}
    inline double getLocusEffect(unsigned short i)const{return locusEffect[i];}
    inline unsigned short getTraitId()const{return traitId;}
    inline double getLocusPos()const{return locusPos;}
    inline char getType()const{return type;}    

  };
  
}

#endif
