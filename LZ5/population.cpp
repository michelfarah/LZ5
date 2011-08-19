//****************************************************************************************************
//* population.cpp                                                                                   *
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

#include "population.h"
#include <cmath>
#include <cstdlib>

namespace simulation{

  void Population::createBasePop(Parameters& p,unsigned int size){
    vector<Individual> ger0;
    for(unsigned short i=0; i<size;++i){
      ger0.push_back(Individual(p));      
    }
    pop.push_back(ger0);
    ger0.clear();
  }
  
  
  void Population::createGen(Parameters& p,char mating,unsigned int numoff){    
	  vector<Individual> g;
	  unsigned counter=0;
	  div_t divresult={0,0};
	  unsigned mfratio=0;
	  double fremaining=0;
	  switch(mating){
	  case 'p':
		  break;
	  case 'n':
		  break;
	  case 'r':
		  if(selMales.size()!=0){
			  random_shuffle(selMales.begin(),selMales.end());
		  }
		  if(selFem.size()!=0){
			  random_shuffle(selFem.begin(),selFem.end());
		  }
		  if(selFem.size()==0||selMales.size()==0){
			  std::cout<<"No males or females to mate! The population is extingued!"<<std::endl;
			  break;
		  }

		  divresult=div(selFem.size(),selMales.size());
		  mfratio=divresult.quot;

		  for(unsigned  i=0;i<selMales.size();++i){
			  for(unsigned j=counter;j<mfratio+counter;++j){
				  for(unsigned short k=0;k<numoff;++k){
					  g.push_back(Individual(p,*(selMales[i]),*(selFem[j])));
				  }
			  }
			  counter+=mfratio;
		  }
		  if(divresult.rem!=0){
			  fremaining=(divresult.rem);
			  for(unsigned short i=0;i<fremaining;++i){
				  for(unsigned j=counter;j<counter+1;++j){               //One remaining female per male
					  for(unsigned short k=0;k<numoff;++k){
						  g.push_back(Individual(p,*(selMales[i]),*(selFem[j])));
					  }
				  }
				  counter++;
			  }
		  }
		  pop.push_back(g);
	  }
	  std::cout<<"Generation "<<pop.size()-1<<" created!"<<std::endl;
  }

  unsigned long Population::totalSize(){
	  unsigned long popSize=0;
	  for(unsigned short i=0;i<pop.size();++i){
		  popSize+=pop[i].size();
	  }
	  return popSize;
  }
  
  vector<double>& Population::calcAdVar(vector<double>& var){
    
    vector<double> sumSq(var.size(),0);
    vector<double> totalSum(var.size(),0);
  
    for(unsigned short i=0;i<pop.size();++i){
    	for(unsigned short j=0;j<pop[i].size();++j){
    		for(unsigned short k=0;k<var.size();++k){
    			sumSq[k]+=((pop[i][j].getAdGenVal(k))*(pop[i][j].getAdGenVal(k)));
    			totalSum[k]+=pop[i][j].getAdGenVal(k);
    		}
    	}
    }
    for(unsigned short k=0;k<var.size();++k){
      var[k]=(sumSq[k]-((totalSum[k]*totalSum[k])/totalSize()))/(totalSize());
    }
    return var;
  }
  
  vector<double>& Population::calcGenAdVar(vector<double>& var,unsigned short i){
    vector<double> sumSq(var.size(),0);
    vector<double> totalSum(var.size(),0);
    
    for(unsigned short j=0;j<pop[i].size();++j){
      for(unsigned short k=0;k<var.size();++k){
	sumSq[k]+=((pop[i][j].getAdGenVal(k))*(pop[i][j].getAdGenVal(k)));
	totalSum[k]+=pop[i][j].getAdGenVal(k);
      }
    }
    for(unsigned short l=0;l<var.size();++l){
      var[l]=(sumSq[l]-((totalSum[l]*totalSum[l])/pop[i].size()))/(pop[i].size()-1);
    }
    return var;
  }
  
  vector<double>& Population::calcGenPhenVar(vector<double>& var,unsigned short i){
    vector<double> sumSq(var.size(),0);
    vector<double> totalSum(var.size(),0);
    
    for(unsigned short j=0;j<pop[i].size();++j){
      for(unsigned short k=0;k<var.size();++k){
	sumSq[k]+=((pop[i][j].getPhenVal(k))*(pop[i][j].getPhenVal(k)));
	totalSum[k]+=pop[i][j].getPhenVal(k);
      }
    }
    for(unsigned short l=0;l<var.size();++l){
      var[l]=(sumSq[l]-((totalSum[l]*totalSum[l])/pop[i].size()))/(pop[i].size()-1);
    }
    return var;
  }
  
  vector<double>& Population::calcGenEnvDevVar(vector<double>& evar,unsigned short i){
    vector<double> sumSq(evar.size(),0);
    vector<double> totalSum(evar.size(),0);
    
    for(unsigned short j=0;j<pop[i].size();++j){
      for(unsigned short k=0;k<evar.size();++k){
	sumSq[k]+=((pop[i][j].getEnvDevVal(k))*(pop[i][j].getEnvDevVal(k)));
	totalSum[k]+=pop[i][j].getEnvDevVal(k);
      }
    }
    for(unsigned short l=0;l<evar.size();++l){
      evar[l]=(sumSq[l]-((totalSum[l]*totalSum[l])/pop[i].size()))/(pop[i].size()-1);
    }
    return evar;
  }
  
  vector<double>& Population::calcGrandMean(vector<double>& mean){
    
    vector<double> total(mean.size(),0);

    for(unsigned short i=0;i<pop.size();++i){
      for(unsigned short j=0;j<pop[i].size();++j){
	for(unsigned short k=0;k<mean.size();++k){
	  total[k]+=pop[i][j].getPhenVal(k);
	}
      }
    }
    for(unsigned short k=0;k<mean.size();++k){
      mean[k]=total[k]/totalSize();
    }
    return mean;
  }

  vector<double>& Population::calcGenMean(vector<double>& mean,unsigned short i){
    vector<double> total(mean.size(),0);
    
    for(unsigned short j=0;j<pop[i].size();++j){
      for(unsigned short k=0;k<mean.size();++k){
	total[k]+=pop[i][j].getPhenVal(k);
      }
    }
    for(unsigned short l=0;l<mean.size();++l){
      mean[l]=(total[l]/pop[i].size());
    }
    return mean;
  }

  vector<double>& Population::calcGenAlelleFreq(vector<double>& afreq,unsigned short i){
    afreq.clear();
    
    vector<Chromosome>::iterator cit;    
    
    unsigned int totalLoci=0;    
    
      for(cit=pop[0][0].getGenome().getGenom().begin();cit!=pop[0][0].getGenome().getGenom().end();++cit){
	totalLoci+=cit->getChrom().size();
    }
    afreq.resize(totalLoci,0);
 
    vector<Individual>::iterator iit;    
    vector<Locus>::iterator lit; 

    size_t acsize=0;                                                  //Accumulated Chromosome size
    
    for(iit=pop[i].begin();iit!=pop[i].end();++iit){
      for(cit=iit->getGenome().getGenom().begin();cit!=iit->getGenome().getGenom().end();++cit){
	for(lit=cit->getChrom().begin();lit!=cit->getChrom().end();++lit){
	  for(unsigned short j=0;j<2;++j){
	    if(lit->getAlellesConfig(j)==0){
	      afreq[(lit-(cit->getChrom().begin()))+acsize]+=1.0/(2*pop[i].size());
	    }
	  }
	}
	acsize+=cit->getChrom().size();
      }
      acsize=0;
    }
    return afreq;
  }
  
  void Population::exec(lz5_Result_Struct& e,Parameters& p){    
    if(e.object!=getName())return;
    if(e.method=="createBasePop"){
      createBasePop(p,e._unsigned[0]);
    }else if(e.method=="createGen"){
      createGen(p,e._char[0],e._unsigned[0]);
    }
  }


  //******************************************************************************************************************************************
  //Class Population1's methods                                                                                                              *
  //******************************************************************************************************************************************
  void Population1::createBasePop(Parameters& p,unsigned int size){
    vector<Individual1> ger0;
    for(unsigned short i=0; i<size;++i){
      ger0.push_back(Individual1(p));      
    }
    pop.push_back(ger0);
    ger0.clear();
    tabularMethod(pop.size()-1);
    std::cout<<"Base Population created!"<<std::endl;
  }
  
  void Population1::createGen(Parameters& p,char mating,unsigned int numoff){    
    vector<Individual1> g;
    unsigned counter=0;
    div_t divresult={0,0};
    unsigned mfratio=0;
    double fremaining=0;
    switch(mating){
    case 'p':
      break;
    case 'n':
      break;
    case 'r':
      if(selMales.size()!=0){
	random_shuffle(selMales.begin(),selMales.end());
      }
      if(selFem.size()!=0){	  
	random_shuffle(selFem.begin(),selFem.end()); 
      }		            
      if(selFem.size()==0||selMales.size()==0){
	std::cout<<"No males or females to mate! The population is extingued!"<<std::endl;
	break;
      }
      
      divresult=div(selFem.size(),selMales.size());
      mfratio=divresult.quot;

      for(unsigned  i=0;i<selMales.size();++i){
	for(unsigned j=counter;j<mfratio+counter;++j){
	  for(unsigned short k=0;k<numoff;++k){
	    g.push_back(Individual1(p,*(selMales[i]),*(selFem[j])));
	  }	    
	}
	counter+=mfratio;
      }      
      if(divresult.rem!=0){
	fremaining=(divresult.rem);
	for(unsigned short i=0;i<fremaining;++i){
	  for(unsigned j=counter;j<counter+1;++j){               //One remaining female per male
	    for(unsigned short k=0;k<numoff;++k){
	      g.push_back(Individual1(p,*(selMales[i]),*(selFem[j])));	      
	    }	    
	  }
	  counter++;
	}
      }
      pop.push_back(g);
      tabularMethod(pop.size()-1);            
    }	
    std::cout<<"Generation "<<pop.size()-1<<" created!"<<std::endl;
  }

 unsigned long Population1::totalSize(){
    unsigned long popSize=0;
    for(unsigned short i=0;i<pop.size();++i){
      popSize+=pop[i].size();
    }
    return popSize;
  }
  
  vector<double>& Population1::calcAdVar(vector<double>& var){
    
    vector<double> sumSq(var.size(),0);
    vector<double> totalSum(var.size(),0);
  
    for(unsigned short i=0;i<pop.size();++i){
      for(unsigned short j=0;j<pop[i].size();++j){
	for(unsigned short k=0;k<var.size();++k){
	  sumSq[k]+=((pop[i][j].getAdGenVal(k))*(pop[i][j].getAdGenVal(k)));
	  totalSum[k]+=pop[i][j].getAdGenVal(k);
	}
      }
    }
    for(unsigned short k=0;k<var.size();++k){
      var[k]=(sumSq[k]-((totalSum[k]*totalSum[k])/totalSize()))/(totalSize());
    }
    return var;
  }
  
  vector<double>& Population1::calcGenAdVar(vector<double>& var,unsigned short i){
    vector<double> sumSq(var.size(),0);
    vector<double> totalSum(var.size(),0);
    
    for(unsigned short j=0;j<pop[i].size();++j){
      for(unsigned short k=0;k<var.size();++k){
	sumSq[k]+=((pop[i][j].getAdGenVal(k))*(pop[i][j].getAdGenVal(k)));
	totalSum[k]+=pop[i][j].getAdGenVal(k);
      }
    }
    for(unsigned short l=0;l<var.size();++l){
      var[l]=(sumSq[l]-((totalSum[l]*totalSum[l])/pop[i].size()))/(pop[i].size()-1);
    }
    return var;
  }
  
  vector<double>& Population1::calcGenPhenVar(vector<double>& var,unsigned short i){
    vector<double> sumSq(var.size(),0);
    vector<double> totalSum(var.size(),0);
    
    for(unsigned short j=0;j<pop[i].size();++j){
      for(unsigned short k=0;k<var.size();++k){
	sumSq[k]+=((pop[i][j].getPhenVal(k))*(pop[i][j].getPhenVal(k)));
	totalSum[k]+=pop[i][j].getPhenVal(k);
      }
    }
    for(unsigned short l=0;l<var.size();++l){
      var[l]=(sumSq[l]-((totalSum[l]*totalSum[l])/pop[i].size()))/(pop[i].size()-1);
    }
    return var;
  }
  
  vector<double>& Population1::calcGenEnvDevVar(vector<double>& evar,unsigned short i){
    vector<double> sumSq(evar.size(),0);
    vector<double> totalSum(evar.size(),0);
    
    for(unsigned short j=0;j<pop[i].size();++j){
      for(unsigned short k=0;k<evar.size();++k){
	sumSq[k]+=((pop[i][j].getEnvDevVal(k))*(pop[i][j].getEnvDevVal(k)));
	totalSum[k]+=pop[i][j].getEnvDevVal(k);
      }
    }
    for(unsigned short l=0;l<evar.size();++l){
      evar[l]=(sumSq[l]-((totalSum[l]*totalSum[l])/pop[i].size()))/(pop[i].size()-1);
    }
    return evar;
  }
  
  vector<double>& Population1::calcGrandMean(vector<double>& mean){
    
    vector<double> total(mean.size(),0);

    for(unsigned short i=0;i<pop.size();++i){
      for(unsigned short j=0;j<pop[i].size();++j){
	for(unsigned short k=0;k<mean.size();++k){
	  total[k]+=pop[i][j].getPhenVal(k);
	}
      }
    }
    for(unsigned short k=0;k<mean.size();++k){
      mean[k]=total[k]/totalSize();
    }
    return mean;
  }

  vector<double>& Population1::calcGenMean(vector<double>& mean,unsigned short i){
    vector<double> total(mean.size(),0);
    
    for(unsigned short j=0;j<pop[i].size();++j){
      for(unsigned short k=0;k<mean.size();++k){
	total[k]+=pop[i][j].getPhenVal(k);
      }
    }
    for(unsigned short l=0;l<mean.size();++l){
      mean[l]=(total[l]/pop[i].size());
    }
    return mean;
  }

  void Population1::tabularMethod(unsigned gnumber){
    vector<double> row;
    if(gnumber==0){                                       //Base population
      for(unsigned i=0;i<pop[gnumber].size();++i){
	for(unsigned j=0;j<pop[gnumber].size();++j){
	  if(i==j)
	    row.push_back(1);
	  else
	    row.push_back(0);
	}
	relTable.push_back(row);
	row.clear();
      }
    }
    else{
      //*****************************************************************
      //Setting Rectangle - BEGINNING                                   *
      //*****************************************************************
      static unsigned parGenSize=0;
      parGenSize+=pop[gnumber-1].size();                       //Size of the parents generation
      for(unsigned i=0;i<parGenSize;++i){ 
	for(unsigned j=parGenSize;j<parGenSize+pop[gnumber].size();++j){	  
	  relTable[i].push_back(0.5*(relTable[i][pop[gnumber][j-parGenSize].getSireId()]+relTable[i][pop[gnumber][j-parGenSize].getDamId()]));
	}
      }
      //Symmetric part
      for(unsigned i=parGenSize;i<parGenSize+pop[gnumber].size();++i){
	for(unsigned j=0;j<parGenSize;++j){
	  relTable[i].push_back(0.5*(relTable[j][pop[gnumber][i-parGenSize].getSireId()]+relTable[j][pop[gnumber][i-parGenSize].getDamId()]));
	}
      }
      //*****************************************************************
      //Setting Triangle - BEGINNING                                    *
      //*****************************************************************
      for(unsigned i=parGenSize;i<parGenSize+pop[gnumber].size();++i){
	for(unsigned j=parGenSize;j<parGenSize+pop[gnumber].size();++j){
	  if(i==j){
	    relTable[i].push_back(1+(0.5*relTable[pop[gnumber][j-parGenSize].getSireId()][pop[gnumber][j-parGenSize].getDamId()]));
	  }
	  else{
	    relTable[i].push_back(0.5*(relTable[i][pop[gnumber][j-parGenSize].getSireId()]+relTable[i][pop[gnumber][j-parGenSize].getDamId()]));
	  }
	}
      }
      //Symmetric part
      for(unsigned i=parGenSize+1;i<parGenSize+pop[gnumber].size();++i){
	for(unsigned j=parGenSize;j<i;++j){
	  relTable[i].push_back(0.5*(relTable[j][pop[gnumber][i-parGenSize].getSireId()]+relTable[j][pop[gnumber][i-parGenSize].getDamId()]));
	}
      }
    }
    //Assigning inbreeding coefficients to individuals
    for(unsigned j=0;j<pop[gnumber].size();++j){
      pop[gnumber][j].setInbreeding(relTable[pop[gnumber][j].getIndId()][pop[gnumber][j].getIndId()]-1);
    }
  }
  
  void Population1::exec(lz5_Result_Struct& e,Parameters& p){    
    if(e.object!=getName())return;
    if(e.method=="createBasePopil"){
      createBasePop(p,e._unsigned[0]);
    }else if(e.method=="createGenil"){
      createGen(p,e._char[0],e._unsigned[0]);
    }
  }
}

