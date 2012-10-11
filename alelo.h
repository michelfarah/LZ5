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

/*A classe alelo tem como funcao representar um alelo, o qual pode ser um alelo marcador
 * ou um alelo com efeito medio
 * */
class Alelo{
 private:
  bool estado;
 public:
  inline Alelo():estado(false){}
  inline void setAlelo(){estado=true;}
  inline bool getAlelo(){return estado;}
};


/*A classe AleloId tem como finalidade criar um alelo marcador com identificao para estudos que envolvem o conceito de locos identicos por descendencia (ibd).*/
class AleloId:public Alelo{
private:
  static unsigned int cont;
  unsigned int id;
public:
  inline AleloId():Alelo(),id(cont){cont++;}
  inline unsigned int getId(){return id;}
};

unsigned int AleloId::cont=0;

#endif
