//****************************************************************************************************
//* ranSel.cpp                                                                                       *
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

#include "ranSel.h"
#include <algorithm>
#include <iostream>

using std::vector;

namespace selection{

  vector<triplet>& RanSel::randomSel(vector<triplet>& cvec,vector<triplet>& vSel,unsigned long sel){      //vSel is a vector where selected individuals' id will be stored. It will avoid to return a local vector as reference

    triplet g;
              
    random_shuffle(cvec.begin(),cvec.end());
    
    for(unsigned short i=0;i<sel;++i){
      g.iId=cvec[i].iId;
      g.gId=cvec[i].gId;
      vSel.push_back(g);	
    }
    return vSel;
  }
      
  void RanSel::exec(lz5::lz5_Result_Struct& e,vector<triplet>& cvec,vector<triplet>& vSel){
    if(e.object!=getName())return;
    if(e.method=="rSel"){
      randomSel(cvec,vSel,e._unsignedLong[0]);
    }
  }
  
}
