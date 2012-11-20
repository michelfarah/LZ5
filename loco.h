//****************************************************************************************************
//* loco.h                                                                                           *
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

#ifndef _LOCO_H_
#define _LOCO_H_

#include<stdlib.h>
#include<time.h>
#include<vector>

#include "alelo.h"

using std::vector;

/*A classe LocoM tem como funcao armazenar o genotipo (configuracao alelica) de cada loco marcador que ira compor um individuo*/

class LocoM{
 private:
  vector <Alelo*> genotipo;
  unsigned short pos;
 public:
 LocoM():genotipo(){};
  void setLoco(bool tipo);
  inline vector<Alelo*> getLoco(){ return genotipo;};
};

/*A classe LocoQ tem como funcao armazenar o genotipo de um loco QTL de um individuo */
class LocoQ:public LocoM {
 private:
  float vgl; /*valor genetico do loco */
 public:
  inline LocoQ():vgl(0){};
  inline void setVGL(float varad, unsigned int qtdQTL){vgl=varad/qtdQTL;};
  inline float getVGL(){return vgl;};
};

#endif
