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

//! Classe para criar um Loco a partir de 2 Alelos
/*!
 * A Classe Loco tem como funcao armazenar o genotipo (configuracao alelica) de cada loco que ira compor um
 * individuo, nao importando o tipo de loco (marcador, QTL ou poligenico).
 * \author Michel Marques Farah e Ricardo da Fonseca
 * \since 20/09/2012
 * \version 1.1
 */

class Loco{
 private:
  vector <Alelo*> genotipo; /*!< Armazena dois ponteiros para dois objetos do Tipo Alelo ou AleloId */ 
  static float vglpol[3]; /*!< Vetor static de 3 posicoes com a contribuicao de cada configuracao dos locos poligenicos */
  static float vglqtl[3]; /*!< Vetor static de 3 posicoes com a contribuicao de cada configuracao dos locos QTL */
  
 public:
  /**
   * Cria um objeto Genotipo vazio.
   */
 Loco():genotipo(){};
  /*! Retorna um vetor com 2 poteiros para dois objetos Alelo */
  inline vector<Alelo*> getLoco(){ return genotipo;}; 
  
  /*! Metodo para retornar a contribuicao dos locos poligenicos dependendo da sua configuracao alelica  
   * \param i - indice que indica a posição no array de contribuicao dos locos poligenicos
   */
  float getVGLpol(unsigned int i){ return vglpol[i]; }; 
  
  /*! Metodo para retornar a contribuicao dos locos QTLs dependendo da sua configuracao alelica  
   * \param i - indice que indica a posição no array de contribuicao dos locos QTLs
   */
  inline float getVGLQTL(unsigned int i){return vglqtl[i];};
  
  /*! Metodo para ajustar a configuracao do loco
   * \param tipo - bool para indicar se ira criar um objeto do tipo Alelo (FALSE) ou do tipo AleloId (TRUE)
   */
  void setLoco(bool tipo);
  
  /*! Metodo para ajustar o vetor static de contribuicao dos locos poligenicos.
   * \param varad - Variancia Aditiva fornecida pelo usuario;
   * \param qtdlocos - Quantidade de Locos Poligenicos que irao formar o genoma do individuo;
   * \param qtdqtl - Quantidade de Locos QTLs que irao formar o genoma do individuo;
   * \param qtdmarcador - Quantidade de Locos Marcadores no genoma de cada individuo;
   * \param freqp - Frequencia alelica (p) dos locos poligenicos (atribui-se a mesma frequencia para todos os locos poligenicos);
   * \param pvaqtl - Proporcao da variancia aditiva que eh explicada pelos QTLs.
   */
  void setVGLPol(float varad, unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float freqp,float pvaqtl);

  /*! Metodo para ajustar o vetor static de contribuicao dos locos QTLs.
   * \param varad - Variancia Aditiva fornecida pelo usuario;
   * \param qtdlocos - Quantidade de Locos Poligenicos que irao formar o genoma do individuo;
   * \param qtdqtl - Quantidade de Locos QTLs que irao formar o genoma do individuo;
   * \param qtdmarcador - Quantidade de Locos Marcadores no genoma de cada individuo;
   * \param freqpqtl - Frequencia alelica (p) dos locos QTLs (atribui-se a mesma frequencia para todos os locos);
   * \param pvaqtl - Proporcao da variancia aditiva que eh explicada pelos QTLs.
   */
  void setVGLQTL(float varad, unsigned int qtdlqtl, float freqpqtl,float pvaqtl);
};

#endif
