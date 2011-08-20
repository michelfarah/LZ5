//****************************************************************************************************
//* sel.cpp                                                                                          *
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

#include "sel.h"
#include <algorithm>
#include <iostream>

using std::vector;

namespace selection{
  
  bool CmpInd::operator()(const simulation::Individual* a,const simulation::Individual* b)const{
    switch(sc){
    case 'p': return a->getPhenVal(pos)>b->getPhenVal(pos);
      break;
    case 'a': return a->getAdGenVal(pos)>b->getAdGenVal(pos);
      break;
    case 'e': return a->getEnvDevVal(pos)>b->getEnvDevVal(pos);
      break;
    default: std::cout<<"This is not a valid option. Phenotypes were selected by default."<<std::endl;
      return a->getPhenVal(pos)>b->getPhenVal(pos);
    }
  }
   
  vector<simulation::Individual*> Sel::selection(unsigned long sel,char gender='m',char sc='p',unsigned short pos=0,bool rev=false){    
    vSel.clear();
    CmpInd comp(sc,pos);
    if(gender=='m'){
      sort(mcandVec.begin(),mcandVec.end(),comp); 
      if(rev==true){
	reverse(mcandVec.begin(),mcandVec.end());
      }
      if(sel>mcandVec.size()){
	sel=mcandVec.size();
      } 
      for(unsigned short i=0;i<sel;++i){
	vSel.push_back(mcandVec[i]);	
      }        
    }
    else{
      sort(fcandVec.begin(),fcandVec.end(),comp);    
      if(rev==true){
	reverse(fcandVec.begin(),fcandVec.end());
      }
      if(sel>fcandVec.size()){
	sel=fcandVec.size();
      } 
      for(unsigned short i=0;i<sel;++i){
	vSel.push_back(fcandVec[i]);	
      }
    }
    return vSel;
  }
  
  void Sel::defineCandidates(simulation::Population& pop,unsigned short ng){
    if(ng>pop.getPop().size()){
      ng=(unsigned short)(pop.getNumGeneration());
    }    
    
    mcandVec.clear();
    fcandVec.clear();
        
    vector<vector<simulation::Individual> >::iterator git;
    vector<simulation::Individual>::iterator iit;
    
    for(git=pop.getPop().end()-ng;git!=pop.getPop().end();++git){
    	for(iit=git->begin();iit!=git->end();++iit){
    		if(iit->getGender()=='m'){
    			mcandVec.push_back(&(*iit));
    		}
    		else{
    			fcandVec.push_back(&(*iit));
    		}
    	}
    }
  }  

  void Sel::defineCandidates(simulation::Population& pop,char t='o'){
    mcandVec.clear();
    fcandVec.clear();    
    
    vector<vector<simulation::Individual> >::iterator git;
    vector<simulation::Individual>::iterator iit;
    
    if(t=='n'){
      git=pop.getPop().end()-1;
      for(iit=git->begin();iit!=git->end();++iit){
	if(iit->getGender()=='m'){
	  mcandVec.push_back(&(*iit));
	}
	else{
	  fcandVec.push_back(&(*iit));
	}	
      }
    }
    else{
      for(git=pop.getPop().begin();git!=pop.getPop().end();++git){
	for(iit=git->begin();iit!=git->end();++iit){
	  if(iit->getGender()=='m'){
	    mcandVec.push_back(&(*iit));
	  }
	  else{
	    fcandVec.push_back(&(*iit));
	  }
	}
      }
    }
  }

  unsigned int Sel::sizecandvec(char g){
    if (g=='m'){
      return mcandVec.size();}
    else {
      return fcandVec.size();}
  }


  //*****************************************************************************************************************************
  //Class Sel1's methods                                                                                                        *
  //*****************************************************************************************************************************
  bool CmpInd1::operator()(const simulation::Individual1* a,const simulation::Individual1* b)const{
    switch(sc){
    case 'p': return a->getPhenVal(pos)>b->getPhenVal(pos);
      break;
    case 'a': return a->getAdGenVal(pos)>b->getAdGenVal(pos);
      break;
    case 'e': return a->getEnvDevVal(pos)>b->getEnvDevVal(pos);
      break;
    default: std::cout<<"This is not a valid option. Phenotypes were selected by default."<<std::endl;
      return a->getPhenVal(pos)>b->getPhenVal(pos);
    }
  }
   
  vector<simulation::Individual1*> Sel1::selection(unsigned long sel,char gender='m',char sc='p',unsigned short pos=0,bool rev=false){    
    vSel.clear();
    CmpInd1 comp(sc,pos);
    if(gender=='m'){
      sort(mcandVec.begin(),mcandVec.end(),comp); 
      if(rev==true){
	reverse(mcandVec.begin(),mcandVec.end());
      }
      if(sel>mcandVec.size()){
	sel=mcandVec.size();
      } 
      for(unsigned short i=0;i<sel;++i){
	vSel.push_back(mcandVec[i]);	
      }        
    }
    else{
      sort(fcandVec.begin(),fcandVec.end(),comp);    
      if(rev==true){
	reverse(fcandVec.begin(),fcandVec.end());
      }
      if(sel>fcandVec.size()){
	sel=fcandVec.size();
      } 
      for(unsigned short i=0;i<sel;++i){
	vSel.push_back(fcandVec[i]);	
      }
    }
    return vSel;
  }
  
  void Sel1::defineCandidates(simulation::Population1& pop,unsigned short ng){
    if(ng>pop.getPop().size()){
      ng=(unsigned short)(pop.getNumGeneration());
    }    
    
    mcandVec.clear();
    fcandVec.clear();
        
    vector<vector<simulation::Individual1> >::iterator git;
    vector<simulation::Individual1>::iterator iit;
    
    for(git=pop.getPop().end();git!=pop.getPop().end()-ng;--git){
      for(iit=git->begin();iit!=git->end();++iit){
	if(iit->getGender()=='m'){
	  mcandVec.push_back(&(*iit));
	}
	else{
	  fcandVec.push_back(&(*iit));
	}
      }
    }
  }  

  void Sel1::defineCandidates(simulation::Population1& pop,char t='o'){
    mcandVec.clear();
    fcandVec.clear();    
    
    vector<vector<simulation::Individual1> >::iterator git;
    vector<simulation::Individual1>::iterator iit;
    
    if(t=='n'){
      git=pop.getPop().end()-1;
      for(iit=git->begin();iit!=git->end();++iit){
	if(iit->getGender()=='m'){
	  mcandVec.push_back(&(*iit));
	}
	else{
	  fcandVec.push_back(&(*iit));
	}	
      }
    }
    else{
      for(git=pop.getPop().begin();git!=pop.getPop().end();++git){
	for(iit=git->begin();iit!=git->end();++iit){
	  if(iit->getGender()=='m'){
	    mcandVec.push_back(&(*iit));
	  }
	  else{
	    fcandVec.push_back(&(*iit));
	  }
	}
      }
    }
  }

}
