//****************************************************************************************************
//* repSim.cpp                                                                                       *
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

#include "repSim.h"

namespace simulation{

  void RepSim::createGenRep(simulation::Population& pop,selection::Sel& s,simulation::Parameters& p,unsigned short ng,unsigned long nm,unsigned long nf,char sc='p',unsigned short pos=0,bool rev=false,char mating='r',unsigned int numoff=2,unsigned int ngen=2){
    for(unsigned int i=0;i<ngen;++i){
      if(ng==0){
	s.defineCandidates(pop,'n');
      }
      else if(ng==1){
	s.defineCandidates(pop,'o');
      }
      else if(ng>1){
	s.defineCandidates(pop,ng);
      }
      else{
	std::cout<<"Invalid option. I will define the candidates considering overllaping generations!"<<std::cout;
	s.defineCandidates(pop,'o');
      }
      pop.setSelMales(s.selection(nm,'m',sc,pos,rev));
      pop.setSelFem(s.selection(nf,'f',sc,pos,rev));
      pop.createGen(p,mating,numoff);
    }
  }

  void RepSim::createSimRep(simulation::Population& pop,selection::Sel& s,simulation::Parameters& p,report::PopRepo& repo,unsigned short ng,unsigned long nm,unsigned long nf,char sc='p',unsigned short pos=0,bool rev=false,char mating='r',unsigned int numoff=2,unsigned int ngen=2,unsigned nsim=100,bool newbase=true,unsigned baseSize=500){
    if(newbase==true){
      for(unsigned i=0;i<nsim;++i){
	pop.getPop().clear();
	pop.createBasePop(p,baseSize);
	createGenRep(pop,s,p,ng,nm,nf,sc,pos,rev,mating,numoff,ngen);
	repo.print(pop,p);
	std::cout<<"Replicate "<<i+1<<" done!"<<std::endl;
      }
    }
    else{
      pop.createBasePop(p,baseSize);
      for(unsigned i=0;i<nsim;++i){
	createGenRep(pop,s,p,ng,nm,nf,sc,pos,rev,mating,numoff,ngen);
	repo.print(pop,p);
	vector<vector<Individual> >::iterator vit;
	pop.getPop().erase(pop.getPop().begin()+1,pop.getPop().end());
	std::cout<<"Replicate "<<i+1<<" done!"<<std::endl;
      }
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Simulation is done!"<<std::endl;
    std::cout<<"Good luck with your analysis..."<<std::endl;
    std::cout<<"Bye!"<<std::endl;
  }

  void RepSim::exec(lz5_Result_Struct& e,simulation::Population& pop,selection::Sel& s,simulation::Parameters& p,report::PopRepo& repo){
    if(e.object!=getName())return;
    if(e.method=="createManyGen"){
      createGenRep(pop,s,p,e._unsignedShort[0],e._unsignedLong[0],e._unsignedLong[1],e._char[0],e._unsignedShort[1],e._bool[0],e._char[1],e._unsigned[0],e._unsigned[1]);
    }else if(e.method=="createManySim"){
      createSimRep(pop,s,p,repo,e._unsignedShort[0],e._unsignedLong[0],e._unsignedLong[1],e._char[0],e._unsignedShort[1],e._bool[0],e._char[1],e._unsigned[0],e._unsigned[1],e._unsigned[2],e._bool[1],e._unsigned[3]);
    }
  }

  //*****************************************************************************************************************************
  //Class RepSim1's methods                                                                                                        *
  //*****************************************************************************************************************************
  void RepSim1::createGenRep(simulation::Population1& pop,selection::Sel1& s,simulation::Parameters& p,unsigned short ng,unsigned long nm,unsigned long nf,char sc='p',unsigned short pos=0,bool rev=false,char mating='r',unsigned int numoff=2,unsigned int ngen=2){
    for(unsigned int i=0;i<ngen;++i){
      if(ng==0){
	s.defineCandidates(pop,'n');
      }
      else if(ng==1){
	s.defineCandidates(pop,'o');
      }
      else if(ng>1){
	s.defineCandidates(pop,ng);
      }
      else{
	std::cout<<"Invalid option. I will define the candidates considering overllaping generations!"<<std::cout;
	s.defineCandidates(pop,'o');
      }
      pop.setSelMales(s.selection(nm,'m',sc,pos,rev));
      pop.setSelFem(s.selection(nf,'f',sc,pos,rev));
      pop.createGen(p,mating,numoff);
    }
  }

  void RepSim1::createSimRep(simulation::Population1& pop,selection::Sel1& s,simulation::Parameters& p,report::PopRepo& repo,unsigned short ng,unsigned long nm,unsigned long nf,char sc='p',unsigned short pos=0,bool rev=false,char mating='r',unsigned int numoff=2,unsigned int ngen=2,unsigned nsim=100,bool newbase=true,unsigned baseSize=500){
    if(newbase==true){
      for(unsigned i=0;i<nsim;++i){
	pop.getPop().clear();
	pop.createBasePop(p,baseSize);
	createGenRep(pop,s,p,ng,nm,nf,sc,pos,rev,mating,numoff,ngen);
	//repo.print(pop,p);
	std::cout<<"Replicate "<<i+1<<" done!"<<std::endl;
      }
    }
    else{
      pop.createBasePop(p,baseSize);
      for(unsigned i=0;i<nsim;++i){
	createGenRep(pop,s,p,ng,nm,nf,sc,pos,rev,mating,numoff,ngen);
	//repo.print(pop,p);
	vector<vector<Individual> >::iterator vit;
	pop.getPop().erase(pop.getPop().begin()+1,pop.getPop().end());
	std::cout<<"Replicate "<<i+1<<" done!"<<std::endl;
      }
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Simulation is done!"<<std::endl;
    std::cout<<"Good luck with your analysis..."<<std::endl;
    std::cout<<"Bye!"<<std::endl;
  }

  void RepSim1::exec(lz5_Result_Struct& e,simulation::Population1& pop,selection::Sel1& s,simulation::Parameters& p,report::PopRepo& repo){
    if(e.object!=getName())return;
    if(e.method=="createManyGenil"){
      createGenRep(pop,s,p,e._unsignedShort[0],e._unsignedLong[0],e._unsignedLong[1],e._char[0],e._unsignedShort[1],e._bool[0],e._char[1],e._unsigned[0],e._unsigned[1]);
    }else if(e.method=="createManySimil"){
      createSimRep(pop,s,p,repo,e._unsignedShort[0],e._unsignedLong[0],e._unsignedLong[1],e._char[0],e._unsignedShort[1],e._bool[0],e._char[1],e._unsigned[0],e._unsigned[1],e._unsigned[2],e._bool[1],e._unsigned[3]);
    }
  }

}
