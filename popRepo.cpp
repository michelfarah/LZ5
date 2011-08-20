//****************************************************************************************************
//* popRepo.cpp                                                                                   *
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

#include "popRepo.h"

using std::cout;
using std::endl;

namespace report{
  
  void PopRepo::print(simulation::Population& pop,simulation::Parameters& par){
    
    //Condensed Report, which is printed on the screen - BEGINNING    
    //Additive Genetic (co)variances Report - BEGINNING
    cout<<"Genetic Additive (Co)Variance(s) inputed by the user: "<<endl;

    for(unsigned short i=0;i<par.getNumTraits();++i){
      for(unsigned short j=0;j<par.getNumTraits();++j){
 	cout<<par.getGenAdCov(i,j)<<"\t";
      }
      cout<<"\n";
    }
    
    cout<<"Genetic Additive (Co)Variance(s) per generation: "<<endl;
    vector<vector<double> >varadd;
           
    for(unsigned short h=0;h<pop.getNumGeneration();++h){
      vector<double> var(par.getNumTraits(),0);
      //cout<<"Generation "<<h<<":"<<endl;
      var=pop.calcGenAdVar(var,h);
      //for (unsigned short i=0;i<par.getNumTraits();++i){
      //cout<<var[i]<<"\t";         
      //}
      varadd.push_back(var);     
      //cout<<endl;
    }
    
    for(unsigned short h=0;h<pop.getNumGeneration();++h){
      cout<<h<<"\t";
      for (unsigned short i=0;i<par.getNumTraits();++i){
	cout<<varadd[h][i]<<"\t";
      }
      cout<<endl;
    }
    //Additive Genetic (co)variances Report - END


   //Phenotypic (co)variances Report - BEGINNING
    cout<<"Phenotypic (Co)Variance(s) per generation: "<<endl;
    
    vector<vector<double> >varphen;
          
    for(unsigned short h=0;h<pop.getNumGeneration();++h){
      vector<double> var(par.getNumTraits(),0);
      //cout<<"Generation "<<h<<":"<<endl;
      var=pop.calcGenPhenVar(var,h);
      //for (unsigned short i=0;i<par.getNumTraits();++i){
      //cout<<var[i]<<"\t";
      //}
      varphen.push_back(var);
      //cout<<endl;
    }
    
    for(unsigned short h=0;h<pop.getNumGeneration();++h){
      cout<<h<<"\t";
      for (unsigned short i=0;i<par.getNumTraits();++i){
	cout<<varphen[h][i]<<"\t";
      }
      cout<<endl;
    }
    //Phenotypic (co)variances Report - END


    //Traits phenotypic means Report - BEGINNING
    cout<<"Traits' phenotypic means inputed by the user: "<<endl;
    
    for(unsigned short i=0;i<par.getNumTraits();++i){
      cout<<"Trait "<<i+1<<" mean: \n";
      cout<<par.getTraitMeans(i)<<"\n";
    }
    
    vector<double> means(par.getNumTraits(),0);
    
    cout<<"Traits phenotypic means per generation: "<<endl;    
    for(unsigned short k=0;k<pop.getNumGeneration();++k){
      cout<<"Generation "<<k<<":"<<endl;
      means=pop.calcGenMean(means,k);
      for(unsigned short j=0;j<par.getNumTraits();++j){
	cout<<means[j]<<"\t";
      }
      cout<<endl;
    }
    //Traits phenotypic means Report - END
    //Heritability report - BEGINNING
    cout<<"Traits' heritabilities inputed by the user: "<<endl;
    
    for(unsigned short i=0;i<par.getNumTraits();++i){
      cout<<"Trait "<<i+1<<" heritability: \n";
      cout<<par.getHeritability(i)<<"\n";
    }
    
    vector<vector<double> > herit(pop.getNumGeneration(),vector<double>(par.getNumTraits(),0));
    cout<<"Traits heritabilities per generation: "<<endl;    
    for(unsigned short k=0;k<pop.getNumGeneration();++k){
      cout<<k<<"\t";
      for(unsigned short j=0;j<par.getNumTraits();++j){
	herit[k][j]=(varadd[k][j]/varphen[k][j]);
       	cout<<herit[k][j]<<"\t";
       	cout<<endl;
      }
    }    
    //Heritability report - END

    //Alelle Frequency report - BEGINNING
    // cout<<"Alelle Frequencies inputed by the user: "<<endl;
   
//       for(unsigned short j=0;j<par.getNumTraits();++j){
//  	cout<<par.getFreqAlelle(j)<<"\t";
//       }
//       cout<<"\n";
    
//     cout<<"Alelles Frequecies per generation: "<<endl;
//     vector<double> afreq;
        
//     double fsum=0;
//     double fmean=0;

//     for(unsigned short h=0;h<pop.getNumGeneration();++h){
//       cout<<"Generation "<<h<<":"<<endl;
//       afreq=pop.calcGenAlelleFreq(afreq,h);
//       for (unsigned short i=0;i<afreq.size();++i){
// 	cout<<afreq[i]<<"\t";
// 	fsum+=afreq[i];
//       }
//       fmean=fsum/afreq.size();
      
//       cout<<endl;
//       cout<<"Average Alelle Frequency over the loci: "<<fmean;
//       cout<<endl;
      
//       fsum=0;
//     }
    //Alelle Frequency report - END
    //Condensed Report, which is printed on the screen - END
    
    
    
    //Complete Report, which is printed to the default file popRepo - BEGINNING
    //Code goes here  
    //Complete Report, which is printed to the default file popRepo - END
  }
  
  void PopRepo::exec(lz5_Result_Struct& e,simulation::Population& pop,simulation::Parameters& par){
    if(e.object!=getName())return;
    if(e.method=="popRepo"){
      print(pop,par);
    }
  }
  
}
