//****************************************************************************************************
//* geracao.h                                                                                        *
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

#ifndef _GERACAO_H_
#define _GERACAO_H_

#include<vector>
#include<algorithm>
#include<math.h>

#include "individuo.h"

using std::vector;

class Geracao {
private:
  vector<Individuo*>geracao;
  unsigned int idg;
  static unsigned int contg;
  float varadg;
  float varresg;
  float varfeng;
  float mediag;
public:
  Geracao():geracao(),idg(contg),varadg(),varresg(),varfeng(),mediag(){contg++;};
  void setGeracao(unsigned int tampb, bool tipo, float varres, float mediavarres, unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float varad, float freqp, float freqpqtl, float pvaqtl, unsigned int qtdcrom);
  void setVaradg();
  void setVarresg();
  void setMediag();

  inline unsigned int getTamGer(){return geracao.size();};
  inline vector<Individuo*> getGeracao(){return geracao;};
  inline float getVaradg(){return varadg;};
  inline float getVarresg(){return varresg;};
  inline float getVarfeng(){return getVaradg()+getVarresg();};
  inline float getMediag(){return mediag;};

};

#endif
