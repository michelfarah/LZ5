//****************************************************************************************************
//* individuo.h                                                                                      *
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

#ifndef _INDIVIDUO_H_
#define _INDIVIDUO_H_

#include<vector>
#include<typeinfo>
#include<algorithm>

#include "loco.h"

class Individuo {
 private:
  vector < Loco* > genoma;
  static vector <unsigned int> posTLocos;
  static vector < unsigned int > tamCrom;
  static unsigned int cont_id;
  unsigned int id;
  unsigned int idp;
  unsigned int idm;
  bool sexo;
  float vres;
 public:
 Individuo():genoma(),sexo(false),id(cont_id),idp(0),idm(0),vres(0){cont_id++;}; 

  void criarIndB(bool tipoid, float varres, float mediavarres);

  void setposTLocos(unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float varad, float freqp, float freqpqtl, float pvaqtl);
  void setGenoma(bool tipoid);
  void setTamCrom(unsigned int qtdlocos, unsigned int qtdcrom);

  float getVad(); 
  inline void setSexo(){sexo=true;}
  void setVres(float varres, float mediavarres);

  inline vector<unsigned int> getposTLocos(){return posTLocos;}
  inline vector<Loco*> getGenoma(){return genoma;}
  inline unsigned int getId(){return id;}
  inline unsigned int getIdp(){return idp;}
  inline unsigned int getIdm(){return idm;}
  inline bool getSexo(){return sexo;}
  inline float getVres(){return vres;}
  inline float getFen(){return getVad()+getVres();}
  
 
};

#endif
  
