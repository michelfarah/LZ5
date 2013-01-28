//****************************************************************************************************
//* populacao.cpp                                                                                    *
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

#include "populacao.h"

void Populacao::criarPopBase(unsigned int tampb, bool tipo, float varres, float mediavarres, unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float varad, float freqp, float freqpqtl, float pvaqtl, unsigned int qtdcrom){
  Geracao *g;
  g=new Geracao;
  g->setGeracao(tampb, tipo, varres, mediavarres, qtdlocos, qtdqtl, qtdmarcador, varad, freqp, freqpqtl, pvaqtl, qtdcrom);
  populacao.push_back(g);
};

float Populacao::getVaradp(){
  float media=0;
  float sum=0;
  float varadp=0;
  unsigned int n=0;
  for(unsigned int i=0;i<populacao.size();i++){
    for(unsigned int j=0;j<populacao[i]->getTamGer();j++){
      media=populacao[i]->getGeracao()[j]->getVad()+media;
      n=n+1;
    }
  }
  media=media/n;
  for (unsigned int i=0;i<populacao.size();i++){
    for (unsigned int j=0;j<populacao[i]->getTamGer();j++){
      sum=pow((populacao[i]->getGeracao()[j]->getVad()-media),2)+sum;
    }
  }
  varadp=sum/(n-1);
  return varadp;
};

float Populacao::getVarresp(){
  float media=0;
  float sum=0;
  float varresp=0;
  unsigned int n=0;
  for(unsigned int i=0;i<populacao.size();i++){
    for(unsigned int j=0;j<populacao[i]->getTamGer();j++){
      media=populacao[i]->getGeracao()[j]->getVres()+media;
      n=n+1;
    }
  }
  media=media/n;
  for (unsigned int i=0;i<populacao.size();i++){
    for (unsigned int j=0;j<populacao[i]->getTamGer();j++){
      sum=pow((populacao[i]->getGeracao()[j]->getVres()-media),2)+sum;
    }
  }
  varresp=sum/(n-1);
  return varresp;
};

float Populacao::getVarfenp(){
  return getVaradp()+getVarresp();
};
