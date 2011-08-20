//****************************************************************************************************
//* tandemRepo.cpp                                                                                   *
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

#include "tandemRepo.h"

namespace report{

void TandemRepo::generateRGG(Tandem& td)const{
	cout<<"Genetic Gains"<<endl;
	cout<<"\t\t";
	for(unsigned int i=0;i<td.getNumGen();++i){
		cout<<i+1<<"\t\t";
	}
	cout<<endl;
	for(unsigned int i=0;i<td.getNumTraits();++i){
		cout<<"Trait "<<i+1<<": ";
		for(unsigned int j=0;j<td.getNumGen();++j){
			cout<<td.getRGG(i,j)<<"\t";
		}
		cout<<endl;
	}
}

void TandemRepo::generateTEV(Tandem& td)const{
	cout<<"Total Economic Gain: "<<endl;
	cout<<"For all generations: "<<endl;
	cout<<td.calcTEV(-1)<<endl;
	cout<<"Total economic gain per generation: "<<endl;
	cout<<"\t\t";
	for(unsigned int g=0;g<td.getNumGen();++g){
		cout<<"Generation "<<g+1<<" :\t"<<td.calcTEV(g)<<endl;
	}
}

void TandemRepo::generateMeansTable(Tandem& td)const{
	cout<<"Population Means"<<endl;
	cout<<"\t\t";
	for(unsigned int i=0;i<td.getNumGen();++i){
		cout<<i+1<<"\t\t";
	}
	cout<<endl;
	for(unsigned int i=0;i<td.getNumTraits();++i){
		cout<<"Trait "<<i+1<<": ";
		for(unsigned int j=0;j<td.getNumGen();++j){
			cout<<td.getMeans(i,j)<<"\t";
		}
		cout<<endl;
	}
}

void TandemRepo::generateNumGenSel(Tandem& td)const{
	cout<< "Number of Generation under Selection"<<endl;
	cout<<endl;
	for(unsigned int i=0;i<td.getNumTraits();++i){
		cout<<"Trait "<<i+1<<": "<<td.getNumGenSel(i)<<endl;
	}
}

void TandemRepo::generateSelOrder(Tandem& td)const{
	cout<<"Selection order: "<<endl;
	vector<unsigned short> order=td.getSelOrder();

	for(unsigned short i=0;i<order.size();++i){
		cout<<order[i]+1<<"\t\t";
	}
	cout<<endl;
}

void TandemRepo::exec(lz5::lz5_Result_Struct& e,Tandem& td){
	if(e.object!=getName())return;
	if(e.method=="tandemRepo"){
		generateSelOrder(td);
		generateRGG(td);
		generateNumGenSel(td);
		generateMeansTable(td);
		generateTEV(td);
	}
}

}
