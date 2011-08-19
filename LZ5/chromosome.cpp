//****************************************************************************************************
//* chromosome.cpp                                                                                   *
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


#include "chromosome.h"

namespace simulation{

  Chromosome::Chromosome(Parameters& p,unsigned short cId):chrom(){
    for(unsigned short i=0;i<p.getChromLoci(cId);++i){
      chrom.push_back(Locus(p,cId));
    }
    for(unsigned short i=0;i<p.getChromQtls(cId).size();++i){
      chrom.push_back(Locus(p,p.getChromQtls(cId)[i].a,p.getChromQtls(cId)[i].b));
    }
    for(unsigned long i=0;i<(unsigned long)(p.getChromSizes(cId)/p.getMarkerDist());++i){
      chrom.push_back(Locus(p,i,p.getMarkerDist()));
    }
    sort(chrom.begin(),chrom.end(),sortLociChrom());
  }
  
}
