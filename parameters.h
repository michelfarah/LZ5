//****************************************************************************************************
//* parameters.h                                                                                     *
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

#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include <vector>
#include <string>
#include "Lz5_Interpreter.h"
#include "specStructures.h"

using std::string;
using std::vector;
using lz5::lz5_Result_Struct;
using std::sort;

namespace simulation
{
  
  class sortNumPol{
  public:
    inline bool operator()(const pair<unsigned short>& a,const pair<unsigned short>& b){return (a.b<b.b);}             //function to sort the vector numPol according to the number of loci.
  };
  
  class Parameters
  {
  private:
    string name;
    vector<double> heritability;                     // Vector of heritabilities.
    vector<vector<double> > genAdCorr;               // Genetic Aditive Correlation matrix.
    vector<vector<double> > genAdCov;                // Genetic Aditive (co)variances.        
    vector<pair<unsigned short> > numPol;            // Number of polygenic loci.
    vector<double> traitMeans;                       // Trait's Means.
    vector<vector<double> > polVal;                  // A1A1 genotype's polygenic additive genetic values. Rows and columns correspond to traits and cell values correspond to the A1A1 additive genetic values for groups of pleitropic loci.
    vector<double> freqAlelle;                       // First Alelle's frequency. If the loci number is equal for some trait, then the frequency should be the same for those traits.
    vector<vector<double> > userQtlsEff;             // Rows are traits, columns are the Qtl's id within trait. Specified as a percentage of the additive genetic variance.
    vector<vector<double> > qtlsGenEff;              // Qtls A1A1 genotype's effect. Calculated by the program.
    vector<vector<double> > qtlsAlelleFreq;          // Qtls' A1 alelle frequency.
    vector<vector<pair<double> > >qtlPos;            // Qtls' position. Rows are traits and colums are the Qtls. The a data member in the pair is the chromosome in which the Qtl is allocated and the b data member is the position itself. 
    vector<unsigned> chromSizes;                     // Chromosomes' sizes.
    vector<unsigned> chromLoci;                      // Number of Loci per chromosome
    vector<vector<pair<unsigned short> > >chromQtls; // It keeps a list of which chromosome the QTLs are located. The rows corresponds to chromosomes and the columns to QTLs.
    vector<vector<double> >markerPos;                // Rows are the chromosomes, columns are the index of markers' position  and the elements are the markers' position themselves. The number of columns (size of inner vector) gives the number of markers in that chromosome. All this information comes, usually, from a reading of a map file.  
    vector<double> markerChrom;                      // Distance between two markers. It is used if one consider that all markers are evenly spaced.
    vector<double> vcc;                              // Vector of changing criteria for tandem selection method;
    vector<double> vec;                              // Vector of economic values for tandem method;
    string species;                                  // Species to be simulated.
    unsigned simType;                                // Simulation type.
    unsigned long basePopSize;                       // Base Population Size.
    unsigned long numMale;                           // Number of males per generation.
    unsigned long numFem;                            // Number of females per male per generation.
    unsigned long numOff;                            // Progeny size per mate.
    unsigned numGen;                                 // Number of generations.
    unsigned rep;                                    // Simulation's number of replicates.
    unsigned genomeSize;                             // Genome's Size.
    unsigned numChrom;                               // Number of Chromosomes in the genome.
    double recombRate;                               // Recombination rate.
    unsigned short numTraits;                        // Number of traits.
    double markerDist;                               // Distance between two markers                               
  
  public:
    inline Parameters():name(),heritability(),genAdCorr(),genAdCov(),numPol(),traitMeans(),polVal(),freqAlelle(),userQtlsEff(),qtlsGenEff(),qtlsAlelleFreq(),qtlPos(),chromSizes(),chromLoci(),chromQtls(),markerPos(),markerChrom(),vcc(),vec(),species("0"), simType(0),basePopSize(0),numMale(0),numFem(0),numOff(0),numGen(0),rep(0),genomeSize(0),numChrom(0),recombRate(0),numTraits(0),markerDist(0){};

    void calcAdCov();
    void adjAdVar();                                //This method adjust the additive genetic variance in order to accomodate the qtl's effects.
    void calcPolVal();
    void calcQtlGenEff();
    
    inline void setName(string n){name=n;}
    void setChromQtls();
    void setSimType();
    void setSpecies(); 
    void setGenomeSize();
    void setNumChrom(); 
    void setChromLoci();
    void setChromSizes();
    void setRecombRate();
    void setMarkerDist();
    void setMarkerChrom();
    void setNumTraits(); 
    void setNumPol(); 
    void setFreqAlelle();
    void setNumQtls(); 
    void setFreqQtls();
    void setEffQtls(); 
    void setPosQtls(); 
    void setHeritability();
    void setTraitMeans();
    void setGenAdCov();
    void setGenAdCorr();
    void setBasePopSize();
    void setNumGen();
    void setNumMale();
    void setNumFem();
    void setNumOff();
    void setRep();

    // Métodos da Interface de Comandos
    void setSpecies(string, double, unsigned);
    void setGenome(unsigned, unsigned, double, unsigned);
    void setMarker(unsigned);
    void setTrait(short, short, double, int);
    void setQtls(unsigned,unsigned,short,short,double,double);
    void setParTrait(unsigned,double,double,double);
    void setCorr(unsigned, unsigned, double);
    void setSelMethod();
    
    inline string getName()const {return name;}
    inline double getHeritability(short i)const {return heritability[i];}
    inline unsigned getHeritabilitySize() const {return heritability.size();}
    inline double getGenAdCorr(short i, short j)const {return genAdCorr[i][j];}
    inline double getGenAdCov(short i, short j)const {return genAdCov[i][j];}
    inline unsigned short getNumPol(short i)const{return numPol[i].b;}
    inline vector<pair<unsigned short> >& getNumPol(){return numPol;}
    inline double getTraitMeans(short i)const {return traitMeans[i];}
    inline double getPolVal(short i, short j)const {return polVal[i][j];}
    inline double getFreqAlelle(short i)const {return freqAlelle[i];}
    inline vector<vector<double> >& getUserQtlsEff(){return userQtlsEff;}
    inline double getUserQtlsEff(short i,short j)const{return userQtlsEff[i][j];}
    inline size_t getUserQtlsEffSize() const {return userQtlsEff.size();}                      //Return collumns size of userQtlsEff
    inline size_t getUserQtlsEff(short b) const{return userQtlsEff[b].size();}                 // Return rows size of userQtlsEff' matrix
    inline vector<vector<double> >& getQtlsGenEff(){return qtlsGenEff;}
    inline double getQtlsGenEff(short i, short j)const{return qtlsGenEff[i][j];}

    inline double getQtlPosA(short i, short j) {return qtlPos[i][j].a;}
    inline double getQtlPosB(short i,short j){return qtlPos[i][j].b;}

    inline double getQtlsAlellesFreq(short i,short j)const{return qtlsAlelleFreq[i][j];}
    inline unsigned getChromSizes(short i)const{return chromSizes[i];}
    inline double getMarkerChrom(short i)const{return markerChrom[i];}
    inline unsigned getChromLoci(short i)const{return chromLoci[i];}
    inline vector<pair<unsigned short> >& getChromQtls(short chromId){return chromQtls[chromId];}
    inline unsigned long getBasePopSize()const {return basePopSize;}
    inline unsigned long getNumMale()const {return numMale;}
    inline unsigned long getNumFem()const {return numFem;}
    inline unsigned long getNumOff()const {return numOff;}
    inline unsigned getNumGen()const {return numGen;}
    inline unsigned getRep()const {return rep;}
    inline unsigned getGenomeSize()const {return genomeSize;}
    inline unsigned getNumChrom()const {return numChrom;}
    inline double getRecombRate()const {return recombRate;}
    inline string getSpecies()const {return species;}
    inline unsigned short getNumTraits()const{return numTraits;}
    inline double getMarkerDist() const {return markerDist;}
    inline unsigned getSimType() const {return simType;} //Função usada para controlar o relatório completo!

    vector<double> getVcc();
    vector<double> getVec();

    
    void input();

    void exec(lz5_Result_Struct& e);
    
   
  };
}
#endif



























