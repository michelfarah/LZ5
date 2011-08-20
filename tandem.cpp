//****************************************************************************************************
//* tandem.cpp                                                                                       *
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

#include "tandem.h"

namespace selection{

void Tandem::tandemSel(simulation::Population& pop, unsigned long selm,unsigned long self,char sc,bool rev,unsigned short ng,simulation::Parameters& p,char mating,int noff){
	vector<double> means(p.getNumTraits(),0);
	vector<double> mean0(p.getNumTraits(),0);
	vector<double> mean1(p.getNumTraits(),0);

	setEvcc(p);
	mean0=pop.calcGrandMean(means);

	std::map<double,pair<double> >::reverse_iterator mit;
	unsigned short genCounter=0;
	for(mit=evcc.rbegin();mit!=evcc.rend();++mit){
		while(mean1[mit->second.a]<mit->second.b){
			defineCandidates(pop,ng);
			pop.setSelMales(selection(selm,'m',sc,mit->second.a,rev));
			pop.setSelFem(selection(self,'f',sc,mit->second.a,rev));
			pop.createGen(p,mating,noff);
			mean1=pop.calcGrandMean(means);
			GGR.push_back(calcGGR(mean0,mean1));
			mean0=mean1;
			trait_means.push_back(mean1);
			genCounter++;
		}
		NumGenSel[mit->second.a]=genCounter;
		genCounter=0;
	}
}

vector<double> Tandem::calcGGP(double i, vector<double> h, vector<double> dp, vector<vector<double> > r){
	//double GG=i*h*dp;
}

vector<double> Tandem::calcGGR(vector<double>& mean0,vector<double>& mean1){
	vector<double> tempRGG;
	for(unsigned int i=0;i<mean0.size();++i){
		tempRGG.push_back(mean1[i]-mean0[i]);
	}
	return tempRGG;
}

double Tandem::calcTEV(int g){
	std::map<double,pair<double> >::iterator mit;
	if(g==-1){
		vector<double> temp;
		double tev=0;
		unsigned int j;
		for(unsigned int i=0;i<GGR.size();++i){
			for(mit=evcc.begin(),j=0;mit!=evcc.end(),j<GGR[i].size();++mit,++j){
				tev+=(mit->first)*GGR[i][j];
			}
		}
		return tev;
	}
	else{
		vector<double> temp;
		double tev=0;
		unsigned int j;
		for (j=0, mit=evcc.begin();j<GGR[g].size(), mit!=evcc.end();++j, ++mit){
			tev+=(mit->first)*GGR[g][j];
		}
		return tev;
	}
}


void Tandem::setEvcc(simulation::Parameters& p){
	vector<double> ev=p.getVec();
	vector<double> cc=p.getVcc();
	vector<pair<double> > temp(p.getNumTraits(),pair<double>());

	for(unsigned int i=0;i<temp.size();++i){
		temp[i].a=i;
		temp[i].b=cc[i];
	}
	for (unsigned short i=0;i<p.getNumTraits();++i){
		evcc[ev[i]]=temp[i];
	}
}

vector<unsigned short> Tandem::getSelOrder()const{
	std::map<double,pair<double> >::const_reverse_iterator mit;
	vector<unsigned short> order;
	for(mit=evcc.rbegin();mit!=evcc.rend();++mit){
		order.push_back(mit->second.a);
	}
	return order;
}

void Tandem::exec(lz5::lz5_Result_Struct& e,simulation::Parameters& p,simulation::Population& pop){
	if(e.object!=getName())return;
	if(e.method=="tandem"){
		tandemSel(pop,e._unsignedLong[0],e._unsignedLong[1],e._char[0],e._bool[0],e._unsignedShort[0],p,e._char[1],e._int[0]);
	}
}

}

// TODO: Implementar função de ganhos genéticos preditos.
// TODO: Reordenar características após seleção para mostrar no relatório.
// TODO: Implementar função para cálculo de ganhos econômicos preditos.
// TODO: Calcular quantas gerações cada característica foi selecionada.
// TODO: Implementar seleção por meio de número de gerações como critério de troca.
