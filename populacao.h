//****************************************************************************************************
//* populacao.h                                                                                      *
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

#ifndef _POPULACAO_H_
#define _POPULACAO_H_

#include<vector>

#include "geracao.h"

using std::vector;

//! Cria uma Populacao, constituida de diversas Geracoes
/*!
 * A classe Populacao tem como funcao armazenar as diversas geracoes simuladas, bem como retornar os parametros
 * geneticos e populacionais da populacao simulada.
 */
class Populacao {
private:
  vector<Geracao*>populacao; /*!< Armazena ponteiros para objetos da classe Geracao. */
public:
  Populacao():populacao(){};

  /*! Metodo para criar uma populacao base (geracao 0), que ira constituir os individuos fundadores da 
   * populacao simulada. 
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
  void criarPopBase(unsigned int tampb, bool tipo, float varres, float mediavarres, unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float varad, float freqp, float freqpqtl, float pvaqtl, unsigned int qtdcrom);

  /*! Retorna a variancia genetica aditiva da populacao. */
  float getVaradp();

  /*! Retorna a variancia residual da populacao. */
  float getVarresp();

  /*! Retorna a variancia fenotipica da populacao. */
  float getVarfenp();

  /*! Retorna a media da caracterista na populacao. */
  void getMediap();

  /*! Retorna o vetor de geracoes que constitui uma populacao. */
  inline vector<Geracao*> getPopulacao(){return populacao;}
};

#endif
