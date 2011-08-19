//****************************************************************************************************
//* indSel.h                                                                                         *
//*                                                                                                  *
//* Copyright (c) 2008 LuCCA-Z (LaboratÃ³rio de ComputaÃ§Ã£o CientÃ­fica Aplicada Ã  Zootecnia),     *
//* Rodovia Comandante JoÃ£o Ribeiro de Barros (SP 294), km 651. UNESP,                              *
//* Dracena, SÃ£o Paulo, Brazil, 17900-000                                                           *
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

#ifndef __INDSEL_H__
#define __INDSEL_H__

#include <vector>
#include "specStructures.h"
#include "Lz5_Interpreter.h"
#include "sel.h"

namespace selection{  

  class IndSel:public Sel{
  private:
    string name;                                 //Needed for interface purposes;
    double selInt;                               //Selection Intensity
    double genInterval;                          //Generation Interval
    double gGenGain;                             //General Genetic Gain
    double mGenGain;                             //Males Genetic Gain
    double fGenGain;                             //Females Genetic Gain
  public:
    inline IndSel():Sel(),name(),selInt(0),genInterval(0),gGenGain(0),mGenGain(0),fGenGain(0){};
    inline virtual ~IndSel(){};


    //Implementar métodos para cálculos específicos da selecão individual.


    //Methods required by the Interface Module - BEGINNING
    inline string getName()const {return name;}
    inline void setName(string n){name=n;}

    void exec(lz5::lz5_Result_Struct& e,simulation::Population& pop);      
    //Methods required by the Interface Module - END
   
  };

  class IndSel1:public Sel1{
  private:
    string name;                                 //Needed for interface purposes;
    double selInt;                               //Selection Intensity
    double genInterval;                          //Generation Interval
    double gGenGain;                             //General Genetic Gain
    double mGenGain;                             //Males Genetic Gain
    double fGenGain;                             //Females Genetic Gain
  public:
    inline IndSel1():Sel1(),name(),selInt(0),genInterval(0),gGenGain(0),mGenGain(0),fGenGain(0){};
    inline virtual ~IndSel1(){};


    //Implementar métodos para cálculos específicos da selecão individual.


    //Methods required by the Interface Module - BEGINNING
    inline string getName()const {return name;}
    inline void setName(string n){name=n;}

    void exec(lz5::lz5_Result_Struct& e,simulation::Population1& pop);      
    //Methods required by the Interface Module - END
   
  };
  
}

#endif
