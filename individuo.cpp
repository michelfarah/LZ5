//****************************************************************************************************
//* individuo.cpp                                                                                    *
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



#include<vector>
#include<stdlib.h>
#include<time.h>
#include<gsl/gsl_rng.h>

#include<iostream>

#include "individuo.h"

using std::vector;

void Individuo::criarIndB(bool tipoid, float varres, float mediavarres){
  setGenoma(tipoid);
  if (rand()%2==1){
    setSexo();
  }
  setVres(varres, mediavarres);
}

float Individuo::getVad()
{
  float sum=0;
  unsigned int salelo=0;
  for(unsigned int i=0; i<posTLocos.size();i++){
    if(posTLocos[i]==0){
      salelo=genoma[i]->getLoco()[0]->getAlelo()+genoma[i]->getLoco()[1]->getAlelo();
      sum=genoma[i]->getVGLpol(salelo)+sum;
    } else {
      if(posTLocos[i]==1){
	salelo=genoma[i]->getLoco()[0]->getAlelo()+genoma[i]->getLoco()[1]->getAlelo();
	sum=genoma[i]->getVGLQTL(salelo)+sum;
      }
    }
  }
  return sum;
} 



void Individuo::setGenoma(bool tipoid)
{
  for(unsigned int i=0; i<posTLocos.size(); i++){
    Loco *ptrloco;
    ptrloco=new Loco;
    ptrloco->setLoco(tipoid);
    genoma.push_back(ptrloco);
  }
};

void Individuo::setTamCrom(unsigned int qtdlocos, unsigned int qtdcrom)
{
  unsigned int pos = qtdlocos/qtdcrom;
  tamCrom.push_back(0);
  for(unsigned int i=0;i<=pos;i++){
    tamCrom.push_back(tamCrom[i]+qtdcrom);
  }
};

void Individuo::setposTLocos(unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float varad, float freqp, float freqpqtl, float pvaqtl)
{

  Loco l;
  l.setVGLPol(varad, qtdlocos, qtdqtl, qtdmarcador, freqp, pvaqtl);
  l.setVGLQTL(varad, qtdlocos, qtdqtl, qtdmarcador, freqpqtl, pvaqtl);

  for (unsigned int i=0;i<qtdlocos;i++){
    posTLocos.push_back(0);
  }
  gsl_rng* pos = gsl_rng_alloc(gsl_rng_mt19937);
  gsl_rng_set(pos,time(0));
  for (unsigned int i=0;i<qtdqtl;i++){
    int q = gsl_rng_uniform_int(pos,qtdlocos);
    if(posTLocos[q]==0){
      posTLocos[q]=1;
    } else {
      i--;
    }
  }
  gsl_rng_set(pos,time(0));
  for (unsigned int i=0;i<qtdmarcador;i++){
    int q = gsl_rng_uniform_int(pos,qtdlocos);
    if(posTLocos[q]==0){
      posTLocos[q]=2;
    } else {
      i--;
    }
  }
  gsl_rng_free(pos);
};

vector <unsigned int>Individuo::posTLocos;
unsigned int Individuo::cont_id=0;
vector<unsigned int>Individuo::tamCrom;
