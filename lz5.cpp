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
#include "individuo.h"

int main(){
  srand(time(NULL));
  //  for(int i=0; i<1; i++){
      AleloId objeto;
  //    if (i%2==0){
  //      objeto.setAlelo();
  //    }
      std::cout << "tamanho do Alelo: " << sizeof(objeto.getAlelo()) << std::endl;
  //    std::cout << "tamanho do Id: " << sizeof(objeto.getId()) << std::endl;
  //  }

  LocoM locom;
  std::cout << "loco marcador" << std::endl;
  std::cout<<" loco: " << locom.getLoco()[0].getAlelo() << std::endl;
  std::cout<<" loco: " << locom.getLoco()[1].getAlelo() << std::endl;
  std::cout<<"Consumo mem: " << sizeof(locom.getLoco()) << std::endl;

  LocoQ locoq;
  float varad=10;
  int qtdlocos=5;
  locoq.setLocoQ(varad,qtdlocos);
  std::cout<<"Loco QTL" << std::endl;
  std::cout<<" loco: " << locoq.getLoco()[0].getAlelo() << std::endl;
  std::cout<<" loco: " << locoq.getLoco()[1].getAlelo() << std::endl;
  std::cout<<" vgl: " << locoq.getvgl() << std::endl;
  std::cout<<"Consumo mem loco: " << sizeof(locoq.getLoco()) << std::endl;
  std::cout<<"Consumo mem vgl: " << sizeof(locoq.getvgl()) << std::endl;
  Individuo ind;




  vector<Alelo> gen;
  std::cout << "Tamanho vector: " << sizeof(gen) << std::endl;

  unsigned int i=1; 


  return 0;
}

