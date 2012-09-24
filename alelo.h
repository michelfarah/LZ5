//****************************************************************************************************
//* locus.h                                                                                          *
//*                                                                                                  *
//* Copyright (c) 2008 LuCCA-Z (LaboratÃ³rio de ComputaÃ§Ã£o CientÃ­fica Aplicada Ã  Zootecnia),     *
//* Rodovia Comandante JoÃ£o Ribeiro de Barros (SP 294), km 651. UNESP,                              *
//* Dracena, SÃ£o Paulo, Brazil, 17900-000                                                           *
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
unsigned int AleloId::id=-1;

#ifndef _ALELO_H_
#define _ALELO_H_

/*A classe alelo tem como função representar um alelo, o qual pode ser um alelo marcador ou um alelo com efeito médio*/
class Alelo{
 private:
  bool estado;
 public:
  inline Alelo():estado(true){};
  inline setEstado(){estado=false};
};

/*A classe AleloId tem como finalidade criar um alelo marcador com identificação para estudos que envolvem o conceito de locos idênticos por descendência (ibd).*/
class AleloId:public Alelo{
 private:
  static unsigned int id;
 public:
  inline AleloId():Alelo(){id++};
};
#endif
