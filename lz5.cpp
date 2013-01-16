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
//biblioteca para geração de no. aleatorios
#include<gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "alelo.h"
#include "loco.h"
#include "individuo.h"

//Verificar a Valor residual do individuo;

using std::vector;
using namespace std;

// class Populacao {
// private:
//   vector<Individuo*>populacao;
//   static unsigned int cont_ger;
//   unsigned int geracao;
// public:
//   Populacao():populacao(),geracao(cont_ger){cont_ger++;};
//   inline unsigned int getGeracao(){return geracao;}
//   inline unsigned int getTamGeracao(){return populacao.size();}
// };

// unsigned int Populacao::cont_ger=0;

gsl_rng* prand1 = gsl_rng_alloc(gsl_rng_mt19937);

int main(){
  srand(time(NULL));

  bool tipo=1;
  unsigned int qtdcrom=2;
  unsigned int qtdlocos=20;
  unsigned int qtdqtl=2;
  unsigned int qtdmarcador=1;
  float varad=10;
  float freqp=0.5;
  float freqpqtl=0.5;
  float pvaqtl=20; /*em porcentagem */
  float varres=10;
  float mediavarres=5;

  Individuo ind;
  ind.setposTLocos(qtdlocos, qtdqtl, qtdmarcador, varad, freqp, freqpqtl, pvaqtl);
  ind.setTamCrom(qtdlocos, qtdcrom);

  for (unsigned int j=0; j<2;j++){
    Individuo ind;
    ind.criarIndB(tipo, varres, mediavarres);
    
    cout<<"RESULTADO:" << endl;
    cout << "id: " << ind.getId() << endl;
    cout << "pai: " << ind.getIdp() << endl;
    cout << "mae: " << ind.getIdm() << endl;
    cout << "sexo: " << ind.getSexo() << endl;
    cout << "Vres: " << ind.getVres() << endl;
    cout << "Vad: " << ind.getVad() << endl;
    cout << "Vfen: " << ind.getFen() << endl;
    // cout<< "Genoma" << endl;
    // for (unsigned int i=0; i<qtdlocos; i++){
    //   cout << ind.getGenoma()[i]->getLoco()[0]->getAlelo() << " ";
    //   cout << ind.getGenoma()[i]->getLoco()[1]->getAlelo() << endl;
    // }
    
    // cout << "IDs" << endl;
    // for (unsigned int i=0; i<qtdlocos; i++){
    //   cout << reinterpret_cast<AleloId*>(ind.getGenoma()[i]->getLoco()[0])->getId() << " ";
    //   cout << reinterpret_cast<AleloId*>(ind.getGenoma()[i]->getLoco()[1])->getId() << endl;
    // }
    
  }


  // Loco loco;

  // loco.setVGLPol(varad, qtdlocos, qtdqtl, qtdmarcador, freqp, pvaqtl);
  // loco.setVGLQTL(varad, qtdlocos, qtdqtl, qtdmarcador, freqp, pvaqtl);

  // cout << "VG Poligenico" << endl;
  // cout << "0 - " << loco.getVGLpol(0) << endl;
  // cout << "1 - " << loco.getVGLpol(1) << endl;
  // cout << "2 - " << loco.getVGLpol(2) << endl;

  // cout << "VG QTL" << endl;
  // cout << "0 - " << loco.getVGLQTL(0) << endl;
  // cout << "1 - " << loco.getVGLQTL(1) << endl;
  // cout << "2 - " << loco.getVGLQTL(2) << endl;


  // loco.setLoco(1);
  // cout << "loco: " << loco.getLoco()[0]-> getAlelo() << " id: " << reinterpret_cast<AleloId*>(loco.getLoco()[0])->getId() << endl;
  // cout << "loco: " << loco.getLoco()[1]-> getAlelo() << " id: " << reinterpret_cast<AleloId*>(loco.getLoco()[1])->getId() << endl;



 //Para ajustar a semente
  // gsl_rng_set(prand1,time(0));

 //for (unsigned int i=0; i<10; i++){
  //   double i = gsl_rng_uniform_int(prand1,100);
  //  cout << i << endl;
  // }
  //No final do programa tem q colocar
  // gsl_rng_free(prand1);




//   //Parametros
//   bool tipoid;
//   float varad, varresp, mediavarresp;
//   unsigned int qtdlocos, qtdqtl, qtdcrom;

//   cout << "Tipo de simulação (0 - Alelo sem Id / 1 - Alelo com Id)" << endl;
//   cin >> tipoid;

//   cout << "Variancia aditiva: " << endl;
//   cin >> varad;

//   cout << "Variancia residual da populacao: " << endl;
//   cin >> varresp;

//   cout << "Média Variancia residual populacao: " << endl;
//   cin >> mediavarresp;

//   cout << "Quantidade de locos: " << endl;
//   cin>>qtdlocos; 

//   cout << "Quantidade de locos QTL: " << endl;
//   cin>>qtdqtl; 

//   cout << "Quantidade de cromossomos: " << endl;
//   cin>> qtdcrom;

//   Individuo ind;
 
//   ind.setposQTL(qtdlocos,qtdqtl);
//   ind.setGenoma(tipoid,qtdlocos,qtdqtl,varad);
//   ind.setTamCrom(qtdlocos,qtdcrom);

//   cout << "genoma " <<endl;
//   unsigned int j=0;
//   unsigned int a=ind.getposQTL()[j];
//   for(unsigned int i=0; i<qtdlocos; i++){
//     if(i!=a) {
// cout << "Loco " << i << ": " << ind.getGenoma()[i] -> getLoco()[0] -> getAlelo() << " " << ind.getGenoma()[i] -> getLoco()[1] -> getAlelo() << endl;
//     } else {
//       cout << "Loco " << i << ": " << reinterpret_cast < LocoQ * > (ind.getGenoma()[i]) -> getLoco()[0] -> getAlelo() << " " << reinterpret_cast < LocoQ * > (ind.getGenoma()[i]) -> getLoco()[0] -> getAlelo() << " VGL: " << reinterpret_cast < LocoQ * > (ind.getGenoma()[i]) -> getVGL() << endl;
//       j++;
//       a=ind.getposQTL()[j];
//     }

// //    cout << "Loco " << i << ": " << reinterpret_cast<AleloId * >(ind.getGenoma()[i] -> getLoco()[0]) -> getId() << " " << reinterpret_cast<AleloId * >(ind.getGenoma()[i] -> getLoco()[1]) -> getId() << endl;
//   }
//   ind.setVarres(varresp,mediavarresp);
//   cout<< "varad " << ind.getVarad() << endl;
//   cout<<"varres " << ind.getVarres() << endl;
//   cout<<"Fen " << ind.getFen() << endl;
//   cout << ind.getId() <<endl;
//   cout << ind.getIdp() <<endl;
//   cout << ind.getIdm() <<endl;

  
//   Populacao pop;
//   // LocoM loco;
//   // loco.setLoco(tipoid);
//   // cout << "alelo1 " << loco.getLoco()[0] -> getAlelo() << endl;
//   // cout << "id1 " << reinterpret_cast<AleloId * >( loco.getLoco()[0]) -> getId() << endl;
//   // cout << "alelo2 " << loco.getLoco()[1] -> getAlelo() << endl;
//   // cout << "id2 " << reinterpret_cast<AleloId * >( loco.getLoco()[1]) -> getId() << endl;
//   // loco.setVGL(varad,qtdlocos);
//   // cout << "variancia aditiva do loco "<<loco.getVGL() << endl; 
  return 0;
}

