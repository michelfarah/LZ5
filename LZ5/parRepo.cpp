//****************************************************************************************************
//* parRepo.cpp                                                                                   *
//*                                                                                                  *
//* Copyright (c) 2008 LuCCA-Z (Laboratório de Computação Científica Aplicada à Zootecnia),     *
//* Rodovia Comandante João Ribeiro de Barros (SP 294), km 651. UNESP,                              *
//* Dracena, São Paulo, Brazil, 17900-000                                                           *
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

#include "parRepo.h"
#define cian    "\033[36m"
#define red     "\033[31m"
#define color_normal "\033[0m"

using std::cout;
using std::endl;

namespace report{
  
  

  void ParRepo::print(simulation::Parameters& par, string t) {
    
    if(t=="Full")
      {
       	cout<<title<<endl;
	
	cout<<cian<<"Species Loaded: "<<par.getSpecies()<<color_normal<<endl;
	cout<<cian<<"Genome Size loaded: "<<par.getGenomeSize()<<color_normal<<endl;
	cout<<cian<<"Number of Chromosomes loaded: "<<par.getNumChrom()<<color_normal<<endl;
	
	for(unsigned short j=0;j<par.getNumChrom();++j){
	  cout<<cian<<"Chromosome "<<j+1<<"' size is: "<<par.getChromSizes(j)<<color_normal<<endl;
	}
	
	cout<<cian<<"Recombination rate loaded: "<<par.getRecombRate()<<color_normal<<endl;  
	cout<<cian<<"Marker distance loaded: "<<par.getMarkerDist()<<color_normal<<endl;
	
	if (par.getSimType()!=0){
	  cout<<"passa";	
  for(int c=0; c<par.getNumChrom();++c){
	    cout<<cian<<"Marker distance loaded on chromosome "<<c+1<<": "<<par.getMarkerChrom(c)<<color_normal<<endl;
	  }
	}
	else{
	  cout<<"No especificado distância de marcadores"<<endl;
	}
	
	cout<<"Parametros de Caracteristica"<<endl;
	
	cout<<cian<<"Number of Traits: "<<par.getNumTraits()<<color_normal<<endl;
	
	for(unsigned short j=0;j<par.getNumTraits();++j){
	  
	  cout<<"For the Trait "<<j+1<<":"<<endl;
	  
	  cout<<cian<<"Numero de Locos Poligenico da Caracteristica "<<j+1<<": "<<par.getNumPol(j)<<color_normal<<endl;
	  cout<<cian<<"/tValor de cada Loco Poligenico: "<<par.getPolVal(j,j)<<color_normal<<endl;
	  
	  cout<<cian<<"Frequencia de Alelos da Caracteristica "<<j+1<<": "<<par.getFreqAlelle(j)<<color_normal<<endl;
	  
	  if(par.getHeritabilitySize()!=0){
	    
	    cout<<cian<<"Herdabilidade da Característica "<<j+1<<": "<<par.getHeritability(j)<<color_normal<<endl;
	    
	    cout<<cian<<"Trait means da Característica "<<j+1<<": "<<par.getTraitMeans(j)<<color_normal<<endl;
	    
	    cout<<cian<<"Variância Genética Aditiva da Característica "<<j+1<<": "<<par.getGenAdCov(j,j)<<color_normal<<endl;  
	  }
	  else{cout<<"None Parameters of tratis input!"<<endl;}
	  
	  if(par.getUserQtlsEffSize()!=0) {
	    
	    for(short b=0;b<par.getUserQtlsEff(j);++b){
	      
	      
	      cout<<cian<<"Posição do Qtl no chromossomo "<<par.getQtlPosA(j,b)<<": "<<par.getQtlPosB(j,b)<<color_normal<<endl;
	      cout<<cian<<"A Frequencia do Qtl: "<<par.getQtlsAlellesFreq(j,b)<<color_normal<<endl;
	      cout<<cian<<"E o Efeito em % fornecido pelo usuário: "<<par.getUserQtlsEff(j,b)<<color_normal<<endl;
	      cout<<cian<<"Efeito calculado do Qtl: "<<par.getQtlsGenEff(j,b)<<color_normal<<endl;
		}
	  }
	  else {cout<<"None Qtls loaded!"<<endl;}
	  
	  cout<<endl;
	}
	
	//COLOCAR CORRELAÇÃO

	cout<<"Parametros de População"<<endl;
	cout<<cian<<"Tamanho da população base: "<<par.getBasePopSize()<<color_normal<<endl;
cout<<cian<<"Quantidade de gerações a serem simuladas: "<<par.getNumGen()<<color_normal<<endl; 
 cout<<endl;
 cout<<"Parametros de Seleção"<<endl;      
 cout<<cian<<"Número de machos selecionados: "<<par.getNumMale()<<color_normal<<endl;
  cout<<cian<<"Número de femeas por macho selecionadas: "<<par.getNumFem()<<color_normal<<endl;
cout<<cian<<"Número de  progenie por acasalamento: "<<par.getNumOff()<<color_normal<<endl;
cout<<cian<<"Quantidade de replicações da simulação: "<<par.getRep()<<color_normal<<endl;


}
    
        
    //Relatório Parcial
    else if(t=="Genome"){
      
      cout<<title<<endl;
      cout<<header<<endl;
      cout<<endl;
      cout<<cian<<"Genome Size loaded: "<<par.getGenomeSize()<<color_normal<<endl;
      cout<<cian<<"Number of Chromosomes loaded: "<<par.getNumChrom()<<color_normal<<endl;
      
      for(unsigned short j=0;j<par.getNumChrom();++j){
	cout<<cian<<"Chromosome "<<j+1<<"' size is: "<<par.getChromSizes(j)<<color_normal<<endl;
      }
      
      cout<<cian<<"Recombination rate loaded: "<<par.getRecombRate()<<color_normal<<endl;  
      cout<<cian<<"Marker distance loaded: "<<par.getMarkerDist()<<color_normal<<endl;
      
    }
    
    else if(t=="Trait"){
      
      cout<<title<<endl;
      cout<<header<<endl;
      cout<<endl;
      
      cout<<cian<<"Number of Traits: "<<par.getNumTraits()<<color_normal<<endl;
      cout<<endl;
      for(unsigned short j=0;j<par.getNumTraits();++j){
	
	cout<<"For the Trait "<<j+1<<":"<<endl;
	
	cout<<cian<<"Numero de Locos Poligenico da Caracteristica "<<j+1<<": "<<par.getNumPol(j)<<color_normal<<endl;
	
	cout<<cian<<"Frequencia de Alelos da Caracteristica "<<j+1<<": "<<par.getFreqAlelle(j)<<color_normal<<endl;
	
  	cout<<cian<<"Herdabilidade da Característica "<<j+1<<": "<<par.getHeritability(j)<<color_normal<<endl;
	
	cout<<cian<<"Trait means da Característica "<<j+1<<": "<<par.getTraitMeans(j)<<color_normal<<endl;
	
	cout<<cian<<"Variância Genética Aditiva da Característica "<<j+1<<": "<<par.getGenAdCov(j,j)<<color_normal<<endl;  
	
	cout<<endl;
      }
    } 
    
    else if(t=="Qtls"){
      
      cout<<title<<endl;
      cout<<header<<endl;    
      cout<<endl;

      for(unsigned short i=0;i<par.getUserQtlsEffSize();++i){

	cout<<"For the Trait "<<i+1<<":"<<endl;
	for(short j=0;j<par.getUserQtlsEff(i);++j){
	  
	  if(par.getQtlPosA(i,j)!=0){
	  cout<<cian<<"Posição do Qtl no chromossomo "<<par.getQtlPosA(i,j)<<": "<<par.getQtlPosB(i,j)<<color_normal<<endl;
	  cout<<cian<<"A Frequencia do Qtl: "<<par.getQtlsAlellesFreq(i,j)<<color_normal<<endl;
	  cout<<cian<<"E o Efeito em % : "<<par.getUserQtlsEff(i,j)<<color_normal<<endl;
	  }
	}
      }
    }
    else if(t==""){
      
      
      cout<<title<<endl;
      cout<<header<<endl;
      cout<<endl;
      cout<<cian<<"Genome Size loaded: "<<par.getGenomeSize()<<color_normal<<endl;
      cout<<cian<<"Number of Chromosomes loaded: "<<par.getNumChrom()<<color_normal<<endl;
      
      for(unsigned short j=0;j<par.getNumChrom();++j){
	cout<<cian<<"Chromosome "<<j+1<<"' size is: "<<par.getChromSizes(j)<<color_normal<<endl;
      }
      
      cout<<cian<<"Recombination rate loaded: "<<par.getRecombRate()<<color_normal<<endl;  
      cout<<cian<<"Marker distance loaded: "<<par.getMarkerDist()<<color_normal<<endl;
      
      cout<<cian<<"Number of Traits: "<<par.getNumTraits()<<color_normal<<endl;
      cout<<endl;
      for(unsigned short j=0;j<par.getNumTraits();++j){
	
	cout<<"For the Trait "<<j+1<<":"<<endl;
	
	cout<<cian<<"Numero de Locos Poligenico da Caracteristica "<<j+1<<": "<<par.getNumPol(j)<<color_normal<<endl;
	
	cout<<cian<<"Frequencia de Alelos da Caracteristica "<<j+1<<": "<<par.getFreqAlelle(j)<<color_normal<<endl;
	
	if(par.getHeritabilitySize()!=0){

	  cout<<cian<<"Herdabilidade da Característica "<<j+1<<": "<<par.getHeritability(j)<<color_normal<<endl;
	  
	  cout<<cian<<"Trait means da Característica "<<j+1<<": "<<par.getTraitMeans(j)<<color_normal<<endl;
	  
	  cout<<cian<<"Variância Genética Aditiva da Característica "<<j+1<<": "<<par.getGenAdCov(j,j)<<color_normal<<endl;  
	}
	else{cout<<"None Parameters of tratis input!"<<endl;}
	
       if(par.getUserQtlsEffSize()!=0) {
	  
	  for(short b=0;b<par.getUserQtlsEff(j);++b){
	    
	    
	    cout<<cian<<"Posição do Qtl no chromossomo "<<par.getQtlPosA(j,b)<<": "<<par.getQtlPosB(j,b)<<color_normal<<endl;
	    cout<<cian<<"A Frequencia do Qtl: "<<par.getQtlsAlellesFreq(j,b)<<color_normal<<endl;
	    cout<<cian<<"E o Efeito em % : "<<par.getUserQtlsEff(j,b)<<color_normal<<endl;
	    
	  }
	}
	else {cout<<"None Qtls loaded!"<<endl;}
	
	cout<<endl;
      }
    }
    
    
    else {cout<<"Option Invalid"<<endl;}
    
    }
  
  void ParRepo::exec(lz5_Result_Struct& e,simulation::Parameters& par){
    if(e.object!=getName())return;
    if(e.method=="parRepo"){print(par,e._string[0]);}
    else if (e.method=="setParTitle"){setTitle(e._string[0]);}
    else if (e.method=="setParHeader"){setHeader(e._string[0]);}
    else if (e.method=="setParFooter"){setFooter(e._string[0]);}
    
  }

}
