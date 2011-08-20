//****************************************************************************************************
//* tandemRepo.h                                                                                     *
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
#ifndef __TANDEMREPO_H_
#define __TANDEMREPO_H_

#include <string>
#include <iostream>
#include "tandem.h"
#include "Lz5_Interpreter.h"
#include "baseReport.h"

using std::cout;
using std::endl;
using std::string;
using selection::Tandem;

namespace report{

class TandemRepo:public BaseReport{
private:
	string name;
public:
	inline TandemRepo():BaseReport(),name(){};

	inline ~TandemRepo(){};

	void generateRGG(Tandem& td)const;
	void generateTEV(Tandem& td)const;
	void generateMeansTable(Tandem& td)const;
	void generateNumGenSel(Tandem& td)const;
	void generateSelOrder(Tandem& td)const;
	inline void setName(string s){name=s;}

	inline string getName()const{return name;}

	void exec(lz5::lz5_Result_Struct& e,Tandem& td);
};
}
#endif
