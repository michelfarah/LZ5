//****************************************************************************************************
//* sel.h                                                                                         *
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

#ifndef __SEL_H__
#define __SEL_H__

#include <vector>
#include "specStructures.h"
#include "population.h"

namespace selection{
  
  class CmpInd{                                                                                                   //Functor Definition to compare between two individuals
  private:
    char sc;
    unsigned short int pos;
  public:
    inline CmpInd(char crit='p',unsigned short p=0):sc(crit),pos(p){};
    bool operator()(const simulation::Individual* a,const simulation::Individual* b)const;
    inline char getsc(){return sc;}
    inline unsigned short int getpos(){return pos;}
  };
  
  class Sel{
  private:
    vector<simulation::Individual*> mcandVec;    //Males candidates vector
    vector<simulation::Individual*> fcandVec;    //Females candidates vector
    vector<simulation::Individual*> vSel;        //Selected individuals vector    
  public:
    inline Sel():mcandVec(),fcandVec(),vSel(){};
    inline virtual ~Sel(){};
    
    std::vector<simulation::Individual*> selection(unsigned long sel,char gender,char sc,unsigned short pos,bool rev);      //This function select sel individual from a group of candidates in cvec. If the smallests values of the selection criterion are to be considered, then rev should be set to true, e.g. the order of the vector of candidates will be reversed. Notice that if one desires to select only males or females, those need to be previously separeted and inserted in cvec. Thus this function need to be called twice, one time for each gender.



    //Methods required to work with the Simulation Module - BEGINNING
    void defineCandidates(simulation::Population& pop,unsigned short ng);                                   //Creates a candidates vector based on the last ng generations. 
    void defineCandidates(simulation::Population& pop,char t);                                              //Creates a candidates vector based on the option specified in t. The options are n and o. In these cases, non-overlapping and overlapping generations respectively are performed. Overlapping generations option considers all candidates from base to current generation. Non-overlapping generations option restricts candidates to the last generation.    
    //Methods required to work with the Simulation Module - END
    unsigned int sizecandvec(char g);
  };

  class CmpInd1{                                                                                                   //Functor Definition to compare between two individuals
  private:
    char sc;
    unsigned short int pos;
  public:
    inline CmpInd1(char crit='p',unsigned short p=0):sc(crit),pos(p){};
    bool operator()(const simulation::Individual1* a,const simulation::Individual1* b)const;
    inline char getsc(){return sc;}
    inline unsigned short int getpos(){return pos;}
  };
  
  class Sel1{
  private:
    vector<simulation::Individual1*> mcandVec;    //Males candidates vector
    vector<simulation::Individual1*> fcandVec;    //Females candidates vector
    vector<simulation::Individual1*> vSel;        //Selected individuals vector    
  public:
    inline Sel1():mcandVec(),fcandVec(),vSel(){};
    inline virtual ~Sel1(){};
    
    std::vector<simulation::Individual1*> selection(unsigned long sel,char gender,char sc,unsigned short pos,bool rev);      //This function select sel individual from a group of candidates in cvec. If the smallests values of the selection criterion are to be considered, then rev should be set to true, e.g. the order of the vector of candidates will be reversed. Notice that if one desires to select only males or females, those need to be previously separeted and inserted in cvec. Thus this function need to be called twice, one time for each gender.
    
    
    
    //Methods required to work with the Simulation Module - BEGINNING
    void defineCandidates(simulation::Population1& pop,unsigned short ng);                                   //Creates a candidates vector based on the last ng generations. 
    void defineCandidates(simulation::Population1& pop,char t);                                              //Creates a candidates vector based on the option specified in t. The options are n and o. In these cases, non-overlapping and overlapping generations respectively are performed. Overlapping generations option considers all candidates from base to current generation. Non-overlapping generations option restricts candidates to the last generation.    
    //Methods required to work with the Simulation Module - END
  };
  
}

#endif
