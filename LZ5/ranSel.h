//****************************************************************************************************
//* ranSel.h                                                                                         *
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

#ifndef __RANSEL_H__
#define __RANSEL_H__

#include <vector>
#include "specStructures.h"
#include "Lz5_Interpreter.h"

//*********************************************************************************************************************************************************************
//This class has in its interface methods to be used specifically with LZ5 simulator and other to be used in general purposes. These latter methods are               *
//independent of LZ5 and intend to be available in a Selection Library.                                                                                               *
//*********************************************************************************************************************************************************************

namespace selection{  
    
  class RanSel{
  private:
    std::vector<pairId> candvec;      //Candidates vector. It is useful for use with candidates coming from external files.
    string name;                      //To use with the interface
    double selInt;                    //Selection Intensity
    double genInterval;               //Generation Interval
    double gGenGain;                  //General Genetic Gain
    double mGenGain;                  //Males Genetic Gain
    double fGenGain;                  //Females Genetic Gain    
  public:
    inline RanSel():candvec(),name(),selInt(0),genInterval(0),gGenGain(0),mGenGain(0),fGenGain(0){};

    inline void setName(string n){name=n;}
    
    std::vector<triplet>& randomSel(std::vector<triplet>& cvec,std::vector<triplet>& vSel,unsigned long sel);      //This function select sel individual from a group o candidates in cvec. Notice that if one desires to select only males or females, those need to be previously separeted and inserted in cvec.


    //Methods required by the Interface Module - BEGINNING
    inline string getName()const {return name;}
    void exec(lz5::lz5_Result_Struct& e,vector<triplet>& cvec,vector<triplet>& vSel);      
    //Methods required by the Interface Module - END


    //Methods required to work with the Simulation Module - BEGINNING
   
    //Methods required to work with the Simulation Module - END                
  };
  
}

#endif
