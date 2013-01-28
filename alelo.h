//****************************************************************************************************
//* alelo.h                                                                                          *
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

#ifndef _ALELO_H_
#define _ALELO_H_

#include<iostream>

//! Classe Alelo.
/*!
 *A classe Alelo tem como funcao representar um alelo na forma mais simples, podendo ser 0 ou 1, esta classe
 * apenas representa o estado do alelo, sem armazenar valores ou efeitos para este.
 * Esta eh uma classe base e, dependendo do tipo de simulacao pode-se usar a classe derivada AleloId.
*/
class Alelo{
 private:
  bool estado; /*< armazena o estado do alelo, um valor bool indicando apenas se é FALSE ou TRUE */
 public:
  /**
   * Por padrao o estado inicial do Alelo sempre é FALSE, sempre que chamado o metodo setAlelo() o estado do 
   * alelo se transforma para TRUE
   */
  inline Alelo():estado(false){}
  inline void setAlelo(){estado=true;} /**< Altera o estado do Alelo de FALSE para TRUE */
  inline bool getAlelo(){return estado;} /**< Retorna o estado atual do Alelo */
};


/*A classe AleloId tem como finalidade criar um alelo marcador com identificao para estudos que envolvem 
 * o conceito de locos identicos por descendencia (ibd). Assim, quando desejado, o simulador cria uma 
 * identificacao unica para cada novo Alelo criado.
*/
class AleloId:public Alelo{
private:
  static unsigned int cont; /*< valor static para incrementar toda vez que um AleloId for criado */
  unsigned int id; /*< armazena o ID do Alelo */
public:
  /**
   * Apresenta a mesma configuracao da Clase Base Alelo, porem, cada vez que um AleloId eh criado ele armazena
   * uma identificacao definida pelo contador 'cont'. 
   */
  inline AleloId():Alelo(),id(cont){cont++;}
  inline unsigned int getId(){return id;} /**< Retorna o ID do Alelo */
};



#endif
