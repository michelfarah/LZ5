//****************************************************************************************************
//* repSim.h                                                                                     *
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

#ifndef __REPSIM_H__
#define __REPSIM_H__


#include "population.h"
#include "indSel.h"
#include "parameters.h"
#include "Lz5_Interpreter.h"
#include "popRepo.h"

//* *******************************************************************************************************************************************
//* The RepSim class has the role to gather objects with different tasks and activate them within a loop to create repeations of a particular *       //* process, as create a number of generation or repeations of a simulation scheme.                                                           *
//*********************************************************************************************************************************************
namespace simulation{

  class RepSim{
  private:
    string name;
  public:
    inline RepSim():name(){};

    inline void setName(string n){name=n;}
    inline string getName()const {return name;}

    void createGenRep(simulation::Population& pop,selection::Sel& s,Parameters& p,unsigned short ng,unsigned long nm,unsigned long nf,char sc,unsigned short pos,bool rev,char mating,unsigned int numoff,unsigned int ngen);                      //create ngen generations according to a predefined scheme given by the other arguments in the method.
    
    void createSimRep(simulation::Population& pop,selection::Sel& s,Parameters& p,report::PopRepo& repo,unsigned short ng,unsigned long nm,unsigned long nf,char sc,unsigned short pos,bool rev,char mating,unsigned int numoff,unsigned int ngen,unsigned int nsim,bool newbase,unsigned int baseSize);  //create nsim replicates of the simulation scheme.  

    void exec(lz5_Result_Struct& e,simulation::Population& pop,selection::Sel& s,simulation::Parameters& p,report::PopRepo& repo);
  };  


  class RepSim1{
  private:
    string name;
  public:
    inline RepSim1():name(){};

    inline void setName(string n){name=n;}
    inline string getName()const {return name;}

    void createGenRep(simulation::Population1& pop,selection::Sel1& s,Parameters& p,unsigned short ng,unsigned long nm,unsigned long nf,char sc,unsigned short pos,bool rev,char mating,unsigned int numoff,unsigned int ngen);                      //create ngen generations according to a predefined scheme given by the other arguments in the method.
    
    void createSimRep(simulation::Population1& pop,selection::Sel1& s,Parameters& p,report::PopRepo& repo,unsigned short ng,unsigned long nm,unsigned long nf,char sc,unsigned short pos,bool rev,char mating,unsigned int numoff,unsigned int ngen,unsigned int nsim,bool newbase,unsigned int baseSize);  //create nsim replicates of the simulation scheme.  

    void exec(lz5_Result_Struct& e,simulation::Population1& pop,selection::Sel1& s,simulation::Parameters& p,report::PopRepo& repo);
  };  

}

#endif
