//****************************************************************************************************
//* geracao.cpp                                                                                      *
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

#include "geracao.h"

void Geracao::setGeracao(unsigned int tampb, bool tipo, float varres, float mediavarres, unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float varad, float freqp, float freqpqtl, float pvaqtl, unsigned int qtdcrom){
  if(contg==0){
    Individuo *pind;
    pind=new Individuo;
    pind->setposTLocos(qtdlocos,qtdqtl,qtdmarcador,varad,freqp,freqpqtl,pvaqtl);
    pind->setTamCrom(qtdlocos,qtdcrom);
    pind->criarIndB(tipo,varres,mediavarres);
    geracao.push_back(pind);
    for(unsigned int i=0; i<tampb-1;i++){
      pind=new Individuo;
      pind->criarIndB(tipo,varres,mediavarres);
      geracao.push_back(pind);
    }
  }
}

void Geracao::setMediag(){
  float media = 0;
  for(unsigned int i=0;i<geracao.size();i++){
    media=geracao[i]->getVad()+geracao[i]->getVres()+media;
  }
  media=media/geracao.size();
}

void Geracao::setVaradg(){
  float media = 0;
  float sum=0;
  for(unsigned int i=0;i<geracao.size();i++){
    media=geracao[i]->getVad()+media;
  }
  media=media/geracao.size();
  for(unsigned int i=0;i<geracao.size();i++){
    sum=pow((geracao[i]->getVad()-media),2)+sum;
  }
  varadg=sum/geracao.size()-1;
}

void Geracao::setVarresg(){
  float media = 0;
  float sum=0;
  for(unsigned int i=0;i<geracao.size();i++){
    media=geracao[i]->getVres()+media;
  }
  media=media/geracao.size();
  for(unsigned int i=0;i<geracao.size();i++){
    sum=pow((geracao[i]->getVres()-media),2)+sum;
  }
  varresg=sum/geracao.size()-1;
}

unsigned int Geracao::contg=-1;
