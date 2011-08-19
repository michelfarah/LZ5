//****************************************************************************************************
//* indRepo.cpp                                                                                      *
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

#include "indRepo.h"

using std::cout;
using std::endl;

namespace report{
  
  void IndRepo::print(simulation::Individual& ind,simulation::Parameters& par){
    
    //Condensed Report, which is printed on the screen - BEGINNING    
    cout<<"Individual's phenotypic value:"<<endl;
    for(unsigned short i=0;i<par.getNumTraits();++i){
      cout<<ind.getPhenVal(i)<<"\t";
    }
    cout<<endl;
    
    cout<<"Individual's additive genetic value:"<<endl;
    for(unsigned short i=0;i<par.getNumTraits();++i){
      cout<<ind.getAdGenVal(i)<<"\t";
    }
    cout<<endl;
    
    cout<<"Individual's environment deviation value:"<<endl;
    for(unsigned short i=0;i<par.getNumTraits();++i){
      cout<<ind.getEnvDevVal(i)<<"\t";
    }
    cout<<endl;

    cout<<"Gender: "<<ind.getGender()<<endl;
    //Condensed Report, which is printed on the screen - END
    
    
    //Complete Report, which is printed to the default file popRepo - BEGINNING
    //Code goes here  
    //Complete Report, which is printed to the default file popRepo - END
  }
  
  void IndRepo::exec(lz5_Result_Struct& e,simulation::Population& pop,simulation::Parameters& par){
    if(e.object!=getName())return;
    if(e.method=="indRepo"){
      print(pop.getPop()[e._unsignedShort[0]][e._unsignedShort[1]],par);
    }
  }
  
}
