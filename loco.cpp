//****************************************************************************************************
//* loco.cpp                                                                                         *
//*                                                                                                  *
//* Copyright (c) 2008 LuCCA-Z (Laboratório de Computação Científica Aplicada à Zootecnia),          *
//* Rodovia Comandante João Ribeiro de Barros (SP 294), km 651. UNESP,                               *
//* Dracena, São Paulo, Brazil, 17900-000                                                            *
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

#include<stdlib.h>
#include<time.h>
#include <cmath>

#include "loco.h"

using namespace std;

void Loco::setLoco(bool tipo){
  if (tipo==0){
    for (int i=0; i<2; i++){
      Alelo *ptralelo;
      ptralelo=new Alelo;
      //testando o estado do alelo
      if(rand()%2==0){
	genotipo.push_back(ptralelo);
      } else {
	ptralelo -> setAlelo();
	genotipo.push_back(ptralelo);
      }
    }
  } else {
    for (int i=0; i<2; i++){
      Alelo *ptralelo;
      ptralelo = new AleloId;
      //testando o estado do alelo
      if(rand()%2==0){
	genotipo.push_back(ptralelo);
      } else {
	ptralelo -> setAlelo();
	genotipo.push_back(ptralelo);
      }
    }
  }
}

void Loco::setVGLPol(float varad, unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float freqp,float pvaqtl){
  vglpol[0]=-sqrt((varad*(1-(pvaqtl/100)))/(2*freqp*(1-freqp)*(qtdlocos-qtdqtl-qtdmarcador)));
  vglpol[1]=0;
  vglpol[2]=sqrt((varad*(1-(pvaqtl/100)))/(2*freqp*(1-freqp)*(qtdlocos-qtdqtl-qtdmarcador))); 
}

void Loco::setVGLQTL(float varad, unsigned int qtdqtl, float freqpqtl,float pvaqtl){
  vglqtl[0]=-sqrt((varad*(pvaqtl/100)))/(2*freqpqtl*(1-freqpqtl)*(qtdqtl));
  vglqtl[1]=0;
  vglqtl[2]=sqrt((varad*(pvaqtl/100)))/(2*freqpqtl*(1-freqpqtl)*(qtdqtl));
}


float Loco::vglpol[3];
float Loco::vglqtl[3];

