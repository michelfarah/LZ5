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

//! Cria um genoma que constitui um individuo
/*!
 * A classe Individuo tem como funcao armazenar o genoma, que ira compor o individuo e armazenar tambem 
 * as informacoes de identificacao, como o ID do individuo e os IDs dos pais, bem como o sexo do indivíduo e 
 * o valor do efeito residual, referente a um erro aleatorio de ambiente.
 */

class Individuo {
 private:
  vector < Loco* > genoma; /*!< Armazena os ponteiros para objetos da classe Loco, que ira constituir o genoma do individuo. */
  static vector <unsigned int> posTLocos; /*!< Vetor static com a configuracao do genoma da populacao (0-loco poligenico, 1-loco QTL e 2-loco marcador).*/
  static vector < unsigned int > tamCrom; /*!< Vetor static com o tamanho de cada cromossomo para identificacao no genoma. */
  static unsigned int cont_id; /*!< Inteiro static para incrementar a identificacao do individuo criado. */
  unsigned int id; /*!< Armazena o cont_id antigo, identificando o ID do novo individuo criado. */
  unsigned int idp; /*!< Armazena o ID do pai do novo individuo. */
  unsigned int idm; /*!< Armazena o ID da mae do novo individuo. */
  bool sexo; /*!< Armazena o sexo do novo individuo. */
  float vres; /*!< Armazena o valor do efeito residual no novo individuo. */
 public:
  /**
   * Cria um objeto do tipo Idividuo com sexo (false), o id (cont_id), idp (0), idm (0) e vres (0).
   */
 Individuo():genoma(),sexo(false),id(cont_id),idp(0),idm(0),vres(0){cont_id++;}; 

  /*! Metodo para criar um individuo da Populacao Base.
   * \param tipoid - corresponde ao tipo de alelo a ser criado (0 - sem identificacao, 1 - com identificacao);
   * \param varres - Variancia residual fornecida pelo usuario;
   * \param mediavarres - Media da variancia residual fornecida pelo usuario.
   */
  void criarIndB(bool tipoid, float varres, float mediavarres);

  /*! Metodo para criar as posicoes do diferentes tipos de locos, um vetor static, apresentando a mesma 
   * configuracao para todos os individuos durante todo o processo de simulacao, cria tambem os vetores de
   * efeito de contribuicao para cada loco poligenico e QTL. Esta funcao eh chamada apenas uma vez, no inicio
   * da simulacao. 
   * \param qtdlocos - ver Loco::setVGLPol();
   * \param qtdqtl - ver Loco::setVGLPol();
   * \param qtdmarcador - ver Loco::setVGLPol();
   * \param varad - ver Loco::setVGLPol();
   * \param freqp - ver Loco::setVGLPol();
   * \param freqpqtl - ver Loco::setVGLQTL();
   * \param pvaqtl - ver Loco::setVGLPol();
   */
  void setposTLocos(unsigned int qtdlocos, unsigned int qtdqtl, unsigned int qtdmarcador, float varad, float freqp, float freqpqtl, float pvaqtl);

  /*! Metodo para criar o genoma do individuo.
   * \param tipoid - Ver Loco::setLoco() da classe Loco. 
   */
  void setGenoma(bool tipoid);

  /*! Metodo para criar vetor static com o tamanho dos cromossomos. (O simulador esta ajustando todos os cromossomos com o mesmo tamanho!)
   * \param qtdlocos - Quantidade total de locos que ira compor o genoma do individuo;
   * \param qtdcrom - Quantidade de cromossomos que ira compor o individuo; 
   */
  void setTamCrom(unsigned int qtdlocos, unsigned int qtdcrom);

  /*! Ajusta o Valor de efeito residual (nao genetico) do individuo.
  * \param varres - Variancia residual da populacao;
  * \param mediavarres - Media da variancia residual da populacao.
  */
  void setVres(float varres, float mediavarres);

  /*! Retorna um float com o Valor Genetico Aditivo do individuo. */
  float getVad(); 

  /*! Altera o valor do sexo para TRUE. */
  inline void setSexo(){sexo=true;}

  /*! Retorna o vetor de configuracao do genoma da populacao. */
  inline vector<unsigned int> getposTLocos(){return posTLocos;}

  /*! Retorna o genoma do individuo. */
  inline vector<Loco*> getGenoma(){return genoma;}

  /*! Retorna o ID do individuo. */ 
  inline unsigned int getId(){return id;}

  /*! Retorna o ID do pai do individuo. */
  inline unsigned int getIdp(){return idp;}

  /*! Retorna o ID da mae do individuo. */
  inline unsigned int getIdm(){return idm;}

  /*! Retorna o sexo do individuo. */
  inline bool getSexo(){return sexo;}

  /*! Retorna o Valor de efeito de ambiente (residual) do individuo. */
  inline float getVres(){return vres;}

  /* Retorna o Valor Fenotipoco do individuo. */
  inline float getFen(){return getVad()+getVres();}
  
 
};

#endif
  
