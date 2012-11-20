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

#include "alelo.h"
#include "loco.h"
//#include "individuo.h"

#include<vector>
#include<typeinfo>
#include<algorithm>

using std::vector;
using namespace std;



class Ind {
private:
  vector < LocoM* > genoma;
  static vector<unsigned int > posQTL;
public:
  Ind():genoma(){};

  void setposQTL(unsigned int qtdlocos,unsigned int qtdqtl)
  {
    vector<unsigned int>posicao;
    for(unsigned int i=0; i<qtdlocos; i++){
      posicao.push_back(i);
    }
    for(unsigned int j=0; j<qtdqtl; j++){
      unsigned int a=rand()%qtdlocos;
      posQTL.push_back(posicao[a]);
      posicao.erase(posicao.begin()+a);
      qtdlocos--;
    }
    sort(posQTL.begin(),posQTL.end());
  };

  void setGenoma(bool tipoid, unsigned int qtdlocos, unsigned int qtdqtl,float varad)
  {
    unsigned int j=0;
    unsigned int a=posQTL[j];
    for(unsigned int i=0; i<qtdlocos; i++){
      if(i==a){
	LocoQ *ptrloco;
	ptrloco=new LocoQ;
	ptrloco->setLoco(tipoid);
	ptrloco->setVGL(varad,qtdqtl);
	genoma.push_back(ptrloco);
	j++;
	a=posQTL[j];
      } else {
	LocoM *ptrloco;
	ptrloco=new LocoM;
	ptrloco->setLoco(tipoid);
	genoma.push_back(ptrloco);
      }
    }
  };

  inline vector<LocoM*> getGenoma(){return genoma;}
  inline vector<unsigned int> getposQTL(){return posQTL;}
};
  
vector<unsigned int>Ind::posQTL;

int main(){
  srand(time(NULL));

  //Parametros
  bool tipoid;
  float varad;
  unsigned int qtdlocos, qtdqtl;

  cout << "Tipo de simulação (0 - Alelo sem Id / 1 - Alelo com Id)" << endl;
  cin >> tipoid;

  cout << "Variancia aditiva: " << endl;
  cin >> varad;

  cout << "Quantidade de locos: " << endl;
  cin>>qtdlocos; 

  cout << "Quantidade de locos QTL: " << endl;
  cin>>qtdqtl; 


  Ind ind;
 
  ind.setposQTL(qtdlocos,qtdqtl);

  ind.setGenoma(tipoid,qtdlocos,qtdqtl,varad);
  cout << "genoma " <<endl;
  unsigned int j=0;
  unsigned int a=ind.getposQTL()[j];
  for(unsigned int i=0; i<qtdlocos; i++){
    if(i!=a) {
cout << "Loco " << i << ": " << ind.getGenoma()[i] -> getLoco()[0] -> getAlelo() << " " << ind.getGenoma()[i] -> getLoco()[1] -> getAlelo() << endl;
    } else {
      cout << "Loco " << i << ": " << reinterpret_cast < LocoQ * > (ind.getGenoma()[i]) -> getLoco()[0] -> getAlelo() << " " << reinterpret_cast < LocoQ * > (ind.getGenoma()[i]) -> getLoco()[0] -> getAlelo() << " VGL: " << reinterpret_cast < LocoQ * > (ind.getGenoma()[i]) -> getVGL() << endl;
      j++;
      a=ind.getposQTL()[j];
    }

//    cout << "Loco " << i << ": " << reinterpret_cast<AleloId * >(ind.getGenoma()[i] -> getLoco()[0]) -> getId() << " " << reinterpret_cast<AleloId * >(ind.getGenoma()[i] -> getLoco()[1]) -> getId() << endl;
  }

  

  
  // LocoM loco;
  // loco.setLoco(tipoid);
  // cout << "alelo1 " << loco.getLoco()[0] -> getAlelo() << endl;
  // cout << "id1 " << reinterpret_cast<AleloId * >( loco.getLoco()[0]) -> getId() << endl;
  // cout << "alelo2 " << loco.getLoco()[1] -> getAlelo() << endl;
  // cout << "id2 " << reinterpret_cast<AleloId * >( loco.getLoco()[1]) -> getId() << endl;
  // loco.setVGL(varad,qtdlocos);
  // cout << "variancia aditiva do loco "<<loco.getVGL() << endl; 
  return 0;
}

