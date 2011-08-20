//****************************************************************************************************
//* indSelRepo.h                                                                                         *
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

#ifndef __IND_SEL_REPO__
#define __IND_SEL_REPO__

#include <iostream>
#include <string>
#include "indSel.h"
#include "parameters.h"

using std::string;

namespace report{

class IndSelRepo{
 private:
  string name;
  string title;
  string header;
  string footnote;
 public:
  inline IndSelRepo():name(),title("Report"),header(),footnote(){};
  inline IndSelRepo(string t,string h,string f):name(),title(t),header(h),footnote(f){};


  //void print(selection::IndSel& iSel,simulation::Parameters& par);

  //Methods required by the Interface Module - BEGINNING
  inline void setName(string n){name=n;}
  inline string getName()const {return name;}

  //void exec(lz5_Result_Struct& e,selection::IndSel& iSel,simulation::Parameters& par);
  //Methods required by the Interface Module - END
};

}
#endif
