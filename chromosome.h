//****************************************************************************************************
//* chromosome.h                                                                                     *
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

#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

#include "locus.h"


//*********************************************************************************************************************************************
//* The class sortchrom defines the operator (), which will be used in a sort algorithm.                                                      *
//* The class chromosome draws an chromosome to be included in the individual's genome. Generate more than one chromosome is a need for tea-  *
//* ching porpouses only, for the students it is easier to understand a genome with several chromosomes rather than one. For this reason,     *
//* functions are relatively complex. To professional use, only a single chromosome is sufficient.                                            * 
//*********************************************************************************************************************************************

namespace simulation
{

  class sortLociChrom{
  public:
    inline bool operator()(const Locus& a,const Locus& b){return a.getLocusPos()<b.getLocusPos();}             //function to sort the vector chrom according to the distance between the loci.
  };


  class Chromosome
  {
    
  private:
    vector<Locus> chrom;
    
  public:
    inline Chromosome():chrom(){};
    Chromosome(Parameters& p,unsigned short cId);           //The argument cId is the chromosome's id passed to the chromosome's constructor by the genome's contructor.

    inline vector<Locus>& getChrom(){return chrom;}
  };
}

#endif
