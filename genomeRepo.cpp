//****************************************************************************************************
//* genomeRepo.cpp                                                                                   *
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

#include "genomeRepo.h"

using std::cout;
using std::endl;

namespace report{
  
  void GenomeRepo::print(simulation::Parameters& par){
    
    //Condensed Report, which is printed on the screen - BEGINNING    
    cout<<"Genome's lenght: "<<par.getGenomeSize()<<endl;
    
    cout<<"Genome's number of chromosomes: "<<par.getNumChrom()<<endl;
    
    cout<<"Number of poligenes for each trait: "<<endl;
    for(unsigned short i=0;i<par.getNumTraits();++i){
      cout<<par.getNumPol(i)<<"\t";
    }
    cout<<endl;
    
    cout<<"Recombination rate: "<<par.getRecombRate()<<endl;
    //Condensed Report, which is printed on the screen - END
    
    
    //Complete Report, which is printed to the default file popRepo - BEGINNING
    //Code goes here  
    //Complete Report, which is printed to the default file popRepo - END
  }
  
  void GenomeRepo::exec(lz5_Result_Struct& e,simulation::Parameters& par){
    if(e.object!=getName())return;
    if(e.method=="genomeRepo"){
      print(par);
    }
  }
  
}
