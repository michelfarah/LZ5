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

class Loco{
 private:
  vector <Alelo*> genotipo;
  unsigned short pos;
  static float vglpol[3]; /*valores geneticos dos locos poligenicos*/
  static float vglqtl[3]; /*valores geneticos dos locos QTL*/

 public:
 Loco():genotipo(){};

  inline vector<Alelo*> getLoco(){ return genotipo;};
  float getVGLpol(unsigned int i){ return vglpol[i]; };
  
  inline float getVGLQTL(unsigned int i){return vglqtl[i];};

  void setLoco(bool tipo);
  void setVGLPol(float varad, unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float freqp,float pvaqtl);
  void setVGLQTL(float varad, unsigned int qtdlocos, unsigned int qtdlqtl, unsigned int qtdmarcador, float freqpqtl,float pvaqtl);
};

#endif
