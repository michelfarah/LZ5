//****************************************************************************************************
//* individual.cpp                                                                                   *
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

#include"individual.h"
#include<gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include<ctime>
#include<cmath>

extern gsl_rng* prand;

namespace simulation{
  
  static unsigned long indCounter=0;
  
  Individual::Individual(Parameters& p):genome(p),phenVal(p.getNumTraits()),adGenVal(p.getNumTraits()),envDevVal(p.getNumTraits()),sireId(0),damId(0),indId(indCounter++),gender(pickGender()){
    calcAdGenVal(p);
    calcPhenVal(p);
  }

  Individual::Individual(Parameters& p,Individual& s,Individual& d):genome(p),phenVal(p.getNumTraits()),adGenVal(p.getNumTraits()),envDevVal(p.getNumTraits()),sireId(s.getIndId()),damId(d.getIndId()),indId(indCounter++),gender(pickGender()){
    zygogenesis(p,s,d);    
    calcAdGenVal(p);
    calcPhenVal(p); 
  }
  
  void Individual::calcAdGenVal(Parameters& p){
    vector<Chromosome>::iterator cit;
    vector<Locus>::iterator lit;
    for(cit=genome.getGenom().begin();cit!=genome.getGenom().end();++cit){
      for(lit=cit->getChrom().begin();lit!=cit->getChrom().end();++lit){
	for(unsigned short i=0;i<p.getNumTraits();++i){
	  adGenVal[i]+=lit->getLocusEffect(i);
	}
      }
    }
  }

  void Individual::calcPhenVal(Parameters& p){    
    for(unsigned short i=0;i<p.getNumTraits();++i){
      envDevVal[i] = gsl_ran_gaussian(prand, sqrt(p.getGenAdCov(i,i)*(1/p.getHeritability(i)-1)));    //generating environment deviates;
      phenVal[i]=p.getTraitMeans(i)+adGenVal[i]+envDevVal[i];
    }   
  }

  char Individual::pickGender(){
    double rNumber=gsl_rng_uniform(prand);
    if(rNumber<0.5)
      return 'f'; 
    else
      return 'm';
  }

  void Individual::zygogenesis(Parameters& p,Individual& s,Individual& d){ 
    //******************************************************************
    //*Sampling a chromosome in the individual's parents-BEGINNING     *
    //******************************************************************     
    unsigned short sIndex=0;                                                                    //The index variable refers to the homologues chromosomes: 0 represents the paternal chromosome and 1 represents the maternal one.
    unsigned short dIndex=0;
    
    double sNumber=gsl_rng_uniform(prand);
    if(sNumber<0.5)
      sIndex=1;
    
    double dNumber=gsl_rng_uniform(prand);
    if(dNumber<0.5)
      dIndex=1;
    //******************************************************************
    //*Sampling a chromosome in the individual's parents-END           *
    //******************************************************************
    vector<Chromosome>::iterator icit;
    vector<Chromosome>::iterator scit;
    vector<Chromosome>::iterator dcit;
    vector<Locus>::iterator ilit;
    vector<Locus>::iterator slit;
    vector<Locus>::iterator dlit;
    
    double rbNumber=0;
    
    for(icit=genome.getGenom().begin(),scit=s.genome.getGenom().begin(),dcit=d.genome.getGenom().begin();icit!=genome.getGenom().end(),scit!=s.genome.getGenom().end(),dcit!=d.genome.getGenom().end();++icit,++scit,++dcit){
      for(ilit=icit->getChrom().begin(),slit=scit->getChrom().begin(),dlit=dcit->getChrom().begin();ilit!=icit->getChrom().end(),slit!=scit->getChrom().end(),dlit!=dcit->getChrom().end();++ilit,++slit,++dlit){
	//************************************************************************
	//*Testing and executing recombination for sire's chromosomes-BEGINNING  *
	//************************************************************************
	rbNumber=gsl_rng_uniform(prand);
	if(rbNumber<p.getRecombRate()){
	  if(sIndex==0)
	    sIndex=1;
	  else
	    sIndex=0;
	}
	//************************************************************************
	//*Testing and executing recombination for sire's chromosomes-END        *
	//************************************************************************
	


	//************************************************************************
	//*Testing and executing recombination for dam's chromosomes-BEGINNING   *
	//************************************************************************
	rbNumber=gsl_rng_uniform(prand);
	if(rbNumber<p.getRecombRate()){
	  if(dIndex==0)
	    dIndex=1;
	  else
	    dIndex=0;
	}
	//************************************************************************
	//*Testing and executing recombination for dam's chromosomes-END         *
	//************************************************************************


	ilit->setAlellesConfig(0,1,slit->getAlellesConfig(sIndex),dlit->getAlellesConfig(dIndex));
	ilit->setTraitId(slit->getTraitId());                                                      //It is needed because the method setLocusEffects requires that traitId variable have been set previously. traitId could be copied from sire or dam.
	ilit->setLocusEffect(p);	
      }
    }
  }


  //*********************************************************************************************************************************************
  // Individual1 class' methods                                                                                                            *
  //*********************************************************************************************************************************************

  Individual1::Individual1(Parameters& p):phenVal(p.getNumTraits()),adGenVal(p.getNumTraits()),envDevVal(p.getNumTraits()),mSampling(),sireId(0),damId(0),indId(indCounter++),gender(pickGender()),inbreedingCoef(0){
    calcAdGenVal(p);
    calcPhenVal(p);
  }
  
  Individual1::Individual1(Parameters& p,Individual1& s,Individual1& d):phenVal(p.getNumTraits()),adGenVal(p.getNumTraits()),envDevVal(p.getNumTraits()),mSampling(p.getNumTraits()),sireId(s.getIndId()),damId(d.getIndId()),indId(indCounter++),gender(pickGender()),inbreedingCoef(0){   
    calcAdGenVal(p,s,d);
    calcPhenVal(p); 
  }
  
  void Individual1::calcAdGenVal(Parameters& p){
    for(unsigned short i=0;i<p.getNumTraits();++i){
      adGenVal[i]=gsl_ran_gaussian(prand,sqrt(p.getGenAdCov(i,i)));
    }
  }
  
  void Individual1::calcAdGenVal(Parameters& p,Individual1& s,Individual1& d){
    for(unsigned short i=0;i<p.getNumTraits();++i){
      mSampling[i]=gsl_ran_gaussian(prand,sqrt((0.5-0.25*(s.getInbreedingCoef()+d.getInbreedingCoef()))*p.getGenAdCov(i,i)));
      adGenVal[i]=0.5*(s.getAdGenVal(i)+d.getAdGenVal(i))+mSampling[i];
    }
  }
  
  void Individual1::calcPhenVal(Parameters& p){    
    for(unsigned short i=0;i<p.getNumTraits();++i){
      envDevVal[i] = gsl_ran_gaussian(prand, sqrt(p.getGenAdCov(i,i)*(1/p.getHeritability(i)-1)));    //generating environment deviates;
      phenVal[i]=p.getTraitMeans(i)+adGenVal[i]+envDevVal[i];
    }   
  }
  
  char Individual1::pickGender(){
    double rNumber=gsl_rng_uniform(prand);
    if(rNumber<0.5)
      return 'f'; 
    else
      return 'm';
  }

  
}

