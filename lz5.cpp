//****************************************************************************************************
//* lz5.cpp                                                                                          *
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
#include<typeinfo>
#include<algorithm>
//operacoes matematicas
#include<math.h>
//biblioteca para geração de no. aleatorios
#include<gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "alelo.h"
#include "loco.h"
#include "individuo.h"
#include "geracao.h"
#include "populacao.h"

using std::vector;
using namespace std;





gsl_rng* p = gsl_rng_alloc(gsl_rng_mt19937);

int main(){
  gsl_rng_set(p,time(0));
  bool tipo=1;
  unsigned int qtdcrom=18;
  unsigned int qtdlocos=20;
  unsigned int qtdqtl=0;
  unsigned int qtdmarcador=1;
  float varad=1;
  float freqp=0.5;
  float freqpqtl=0.5;
  float pvaqtl=0; /*em porcentagem */
  float varres=1;
  float mediavarres=0;
  unsigned int tampb=10000;

  Populacao pop;
  pop.criarPopBase(tampb, tipo, varres, mediavarres, qtdlocos, qtdqtl, qtdmarcador, varad, freqp, freqpqtl, pvaqtl,qtdcrom);
  
  // cout << "Tamanho Ger: " << ger.getTamGer() << endl;
  
  // for (unsigned int j=0; j<tampb;j++){
    
  //   //cout<<"RESULTADO:" << endl;
  //   //cout << "id: " << ger.getGeracao()[j]->getId() << endl;
  //   //cout << "pai: " << ger.getGeracao()[j]->getIdp() << endl;
  //   //cout << "mae: " << ger.getGeracao()[j]->getIdm() << endl;
  //   //cout << "sexo: " << ger.getGeracao()[j]->getSexo() << endl;
  //   //cout << ger.getGeracao()[j]->getVres() << endl;
  //   //cout << "Vad: " << ger.getGeracao()[j]->getVad() << endl;
  //   //cout << "Vfen: " << ger.getGeracao()[j]->getFen() << endl;
  //   //cout<< "Genoma" << endl;
  //   //for (unsigned int i=0; i<qtdlocos; i++){
  //   //cout << ind.getGenoma()[i]->getLoco()[0]->getAlelo() << " ";
  //   //cout << ind.getGenoma()[i]->getLoco()[1]->getAlelo() << endl;
  //   //}
    
  //   //cout << "IDs" << endl;
  //   //for (unsigned int i=0; i<qtdlocos; i++){
  //   //cout << reinterpret_cast<AleloId*>(ind.getGenoma()[i]->getLoco()[0])->getId() << " ";
  //   //cout << reinterpret_cast<AleloId*>(ind.getGenoma()[i]->getLoco()[1])->getId() << endl;
  //   //}    
  // }
  pop.getPopulacao()[0]->setVaradg();
  pop.getPopulacao()[0]->setVarresg();
  cout<<"Var aditiva fornecida: "<<varad<<endl;
  cout<<"Var aditiva da ger: " << pop.getPopulacao()[0]->getVaradg()<<endl;
  cout<<"Var res fornecida: " << varres << endl;
  cout<<"Var res da ger: " << pop.getPopulacao()[0]->getVarresg()<<endl;
  cout<<"Var fen da ger: " << pop.getPopulacao()[0]->getVarfeng()<<endl;

  cout<<"Varad Pop " << pop.getVaradp() << endl;
  cout<<"Varres Pop " << pop.getVarresp() << endl;
  cout<<"Varfen Pop " << pop.getVarfenp() << endl;
  gsl_rng_free(p);
  return 0;
}

