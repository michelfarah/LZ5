//****************************************************************************************************
//* locus.cpp                                                                                        *
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

#include"locus.h"
#include<gsl/gsl_rng.h>
#include<ctime>

extern gsl_rng* prand;

namespace simulation{
  
  static unsigned pLociCounter=0;                                                                                    //polygenic loci counter   
   
  Locus::Locus(Parameters& p,unsigned short cId):alellesConfig(2,0),locusEffect(p.getNumTraits(),0),traitId(0),locusPos(0),type('p'){       
    ++pLociCounter;
    setTraitId(p,pLociCounter);
    setAlellesConfig(p);
    setLocusEffect(p);
    setPos(p,cId);

    vector<pair<unsigned short> >::iterator pit=p.getNumPol().end()-1;                                               //If the loci counter overpass the number of loci of the last trait, then the counter must be reset to zero to initiate a new individual.
    if(pLociCounter==p.getNumPol(pit->a)||pLociCounter>p.getNumPol(pit->a))
    pLociCounter=0;       
  }

  Locus::Locus(Parameters& p,unsigned short tId,unsigned short qId,unsigned short cId):alellesConfig(2,0),locusEffect(p.getNumTraits(),0),traitId(tId),locusPos(0),type('q'){       
    setAlellesConfig(p,tId,qId);
    setQtlLocusEffect(p,tId,qId);
    setPos(p,cId);
  }

  Locus::Locus(Parameters& p,unsigned long mId,double dist):alellesConfig(2,0),locusEffect(p.getNumTraits(),0),traitId(),locusPos(0),type('m'){
    setAlellesConfig(p);
    setPos(mId,dist);
  }


  void Locus::setTraitId(Parameters& p,unsigned lc){
    using std::sort;
        
    if(p.getNumTraits()==1)
      traitId=0;
    else{
      sort(p.getNumPol().begin(),p.getNumPol().end(),sortNumPol());                                              //sorting numPol vector by loci number.
      
      vector<pair<unsigned short> >::iterator vit;
      for(vit=p.getNumPol().begin();vit!=p.getNumPol().end();++vit){
	if(lc<vit->b||lc==vit->b){
	  traitId=vit->a;
	  break;
	}
      }
    }    
    
  }

  void Locus::setAlellesConfig(Parameters& p){
    
    double rNum;
    
    //******************************************************
    //paternal alelle sampling-BEGINNING                   *                                    
    //******************************************************    
    rNum=gsl_rng_uniform(prand);
    unsigned short pAlelle=0;

    if (rNum>p.getFreqAlelle(traitId))
      {
	pAlelle = 1;                                                                                             //Otherwise, it is already set to 0.      
      }
    //******************************************************
    //paternal alelle sampling-END                         *                                    
    //******************************************************


    //******************************************************
    //maternal alelle sampling-BEGINNING                   *                                    
    //******************************************************    
    rNum=gsl_rng_uniform(prand);
    unsigned short mAlelle=0;
    
    if (rNum>p.getFreqAlelle(traitId))
      {
	mAlelle = 1;
      }
    //******************************************************
    //maternal alelle sampling-END                         *                                    
    //******************************************************
     
    alellesConfig[0] = pAlelle;
    alellesConfig[1] = mAlelle;    
  }

  void Locus::setAlellesConfig(Parameters& p,unsigned short tId,unsigned short qId){
    
    double rNum;
    
    //******************************************************
    //paternal alelle sampling-BEGINNING                   *                                    
    //******************************************************    
    rNum=gsl_rng_uniform(prand);
    unsigned short pAlelle=0;

    if (rNum>p.getQtlsAlellesFreq(tId,qId))
      {
	pAlelle = 1;                                                                                             //Otherwise, it is already set to 0.             
      }
    //******************************************************
    //paternal alelle sampling-END                         *                                    
    //******************************************************


    //******************************************************
    //maternal alelle sampling-BEGINNING                   *                                    
    //******************************************************    
    rNum=gsl_rng_uniform(prand);
    unsigned short mAlelle=0;
    
    if (rNum>p.getQtlsAlellesFreq(tId,qId))
      {
	mAlelle = 1;
      }
    //******************************************************
    //maternal alelle sampling-END                         *                                    
    //******************************************************
     
    alellesConfig[0] = pAlelle;
    alellesConfig[1] = mAlelle;    
  }

 void Locus::setAlellesConfig(){
    
    double rNum;
    
    //******************************************************
    //paternal alelle sampling-BEGINNING                   *                                    
    //******************************************************    
    rNum=gsl_rng_uniform(prand);
    unsigned short pAlelle=0;

    if (rNum>0.5)                                                                                                //The markers' frequency is fixed to 0.5, for all of them.
      {
	pAlelle = 1;                                                                                             //Otherwise, it is already set to 0.      
      }
    //******************************************************
    //paternal alelle sampling-END                         *                                    
    //******************************************************


    //******************************************************
    //maternal alelle sampling-BEGINNING                   *                                    
    //******************************************************    
    rNum=gsl_rng_uniform(prand);
    unsigned short mAlelle=0;
    
    if (rNum>0.5)
      {
	mAlelle = 1;
      }
    //******************************************************
    //maternal alelle sampling-END                         *                                    
    //******************************************************
     
    alellesConfig[0] = pAlelle;
    alellesConfig[1] = mAlelle;    
  }
  
  void Locus::setLocusEffect(Parameters& p){   
	  for (unsigned short i=traitId;i<p.getNumTraits();++i){                                                     //This method assumes that traitId has been previosly set;
		  if(alellesConfig[0]==0 && alellesConfig[1]==0)
			  locusEffect[i]=p.getPolVal(i,traitId);
		  else if(alellesConfig[0]==1 && alellesConfig[1]==1)
			  locusEffect[i]=-(p.getPolVal(i,traitId));                                                              //Otherwise, it is already set to 0
	  }
  }

  void Locus::setQtlLocusEffect(Parameters& p,unsigned short i,unsigned short j){    
    if(alellesConfig[0]==0 && alellesConfig[1]==0)
      locusEffect[i]=p.getQtlsGenEff(i,j);
    else if(alellesConfig[0]==1 && alellesConfig[1]==1)	
      locusEffect[i]=-p.getQtlsGenEff(i,j);                                                                     //Otherwise, it is already set to 0.    
  }
  
}
