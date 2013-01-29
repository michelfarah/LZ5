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

//! Cria uma Geracao que ira constituir uma populacao.
/*!
 * A classe Geracao aramazena um conjunto de  Individuos contemporaneos. Esta classe tem como funcao facilitar
 * o controle da simulacao por Geracao, fornecendo paramentros populacionais para cada geracao criada.
 */

class Geracao {
private:
  vector<Individuo*>geracao; /*! Armazena ponteiros para objetos do tipo Individuo, que ira constituir uma geracao. */
  unsigned int idg; /*! Armazena a identificacao (ID) de cada geracao criada. */
  static unsigned int contg; /*! Inteiro static para incrementar a identificacao da geracao criada. */
  float varadg; /*! Armazena a variancia genetica aditiva da geracao. */
  float varresg; /*! Armazena a variancia residual da geracao. */
  float mediag; /*! Armazena a media da caracteristica na geracao. */
public:
  Geracao():geracao(),idg(contg),varadg(),varresg(),mediag(){contg++;};

  /*! Metodo para ajustar uma geracao. Se o contg for igual a zero, o simulador cria uma populacao base, 
   * ajustando todos os paramentros necessarios para realizar a simulacao (Individuo::setposTLocos(), 
   * Individuo::setTamCrom(), Individuo::criarIndB()).
   * \param tambp - Tamanho da populacao base;
   * \param tipo - ver Loco::setLoco();
   * \param varres - Variancia Residual fornecida pelo usuario;
   * \param mediavarres - Media da variancia residual fornecida pelo usuario;
   * \param qtdlocos - Quantidade total de locos que ira constituir o genoma do individuo;
   * \param qtdqtl - Quantidade de locos QTLs que ira constituir o genoma do individuo;
   * \param qtdmarcador - Quantidade de locos marcadores no genoma do individuo;
   * \param varad - Variancia genetica aditiva da caracteristica a ser simulada;
   * \param freqp - ver Loco::setVGLPol();
   * \param freqpqtl - ver Loco::setVGLQTL();
   * \param pvaqtl - ver Loco::setVGLPol();
   * \param qtdcrom - Quantidade de cromossomos que ira compor o genoma do individuo.
   */
  void setGeracao(unsigned int tampb, bool tipo, float varres, float mediavarres, unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float varad, float freqp, float freqpqtl, float pvaqtl, unsigned int qtdcrom);

  /*! Ajusta a variancia genetica aditiva da caracterista na geracao. */
  void setVaradg();

  /*! Ajusta a variancia residual (ambiente) da caracteristica na geracao. */ 
  void setVarresg();

  /*! Ajusta a media da caracteristica na geracao. */
  void setMediag();

  /*! Retorna o numero de individuos que constitui a geracao. */
  inline int getTamGer(){return geracao.size();};

  /*! Retorna o vetor de individuo da geracao. */
  inline vector<Individuo*> getGeracao(){return geracao;};

  /*! Retorna a variancia genetica aditiva da geracao */
  inline float getVaradg(){return varadg;};

  /*! Retorna a variancia residual da geracao */
  inline float getVarresg(){return varresg;};

  /*! Retorna a variancia fenotipica da geracao */
  inline float getVarfeng(){return getVaradg()+getVarresg();};

  /*! Retorna a media da caracterista na geracao */
  inline float getMediag(){return mediag;};

};

#endif
