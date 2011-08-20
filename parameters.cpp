#include"parameters.h"
#include<cmath>
#include<iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_rng.h>

#define cian    "\033[36m"
#define red     "\033[31m"
#define color_normal "\033[0m"

extern gsl_rng* prand;

namespace simulation {
  using std::cin;
  using std::cout;
  using std::endl;
  using std::vector;  
  
  void Parameters::calcAdCov() {
    for(unsigned i=0; i<genAdCorr.size(); ++i){
      for(unsigned j=i+1; j<genAdCorr.size(); ++j){
	genAdCov[i][j]=genAdCorr[i][j]*sqrt(genAdCov[i][i]*genAdCov[j][j]);
	genAdCov[j][i]=genAdCov[i][j];
      }
    }
  }
  
  void Parameters::adjAdVar() {
    double tvar=0;
    
    for(unsigned short i=0;i<userQtlsEff.size();++i){
      for(unsigned short j=0;j<userQtlsEff[i].size();++j){
	tvar=genAdCov[i][i];                                                                    //It is assumed that the covariance matrix is already set;
	tvar-=userQtlsEff[i][j]*genAdCov[i][i];
	genAdCov[i][i]=tvar;
      }
    }
  }
  
  void Parameters::calcPolVal() {
    //****************************************************************
    //Converting genAdCov into a gsl matrix-BEGINNING                *
    //****************************************************************
    gsl_matrix* C=gsl_matrix_calloc(genAdCov.size(),genAdCov.size());
    for(unsigned short i=0; i<genAdCov.size();++i){
      for(unsigned short j=0; j<genAdCov.size();++j){
	gsl_matrix_set(C,i,j,genAdCov[i][j]);
      }
    }
    //****************************************************************
    //Converting genAdCov into a gsl matrix-END                      *
    //****************************************************************
    
    
    
    gsl_linalg_cholesky_decomp(C);   //Performing Cholesky Decomposition
    
    
    
    
    //****************************************************************
    //Converting a gsl matrix into STL matrix-BEGINNING              *
    //****************************************************************
    vector<vector<double> > cholCoeff(genAdCov.size(),vector<double>(genAdCov.size(),0));
    for(unsigned short i=0; i<genAdCov.size();++i){
      for(unsigned short j=0; j<=i;++j){
	cholCoeff[i][j]=gsl_matrix_get(C,i,j);	
      }
      std::cout<<std::endl;
    }
    
    gsl_matrix_free(C);
    //****************************************************************
    //Converting a gsl matrix into STL matrix-END                    *
    //****************************************************************
    
    
    
    //****************************************************************
    //Initializing polVal matrix-BEGINNING                           *
    //****************************************************************
    polVal.resize(genAdCov.size());
    for(unsigned short i=0;i<genAdCov.size();++i){
      polVal[i].resize(genAdCov.size());
    }
    //****************************************************************
    //Initializing polVal matrix-END                                 *
    //****************************************************************
    
    double w=0;
    vector<pair<unsigned short> > cNumPol=numPol;                                                                               //cNumPol is a copy of numPol. The reason is to keep numPol with its original values in order to use it at another methods which need it (e.g. setAlellesConfig and setPolVal). The code belows changes cNumPol values instead numPol.

    vector<pair<unsigned short> >::iterator vit;
    vector<pair<unsigned short> >::iterator pit;    
    for(vit=cNumPol.begin();vit!=cNumPol.end();++vit){
    	w=1/(sqrt(2*freqAlelle[vit->a]*(1-freqAlelle[vit->a])*vit->b));
    	for(pit=vit;pit!=cNumPol.end();++pit){
    		polVal[pit->a][vit->a]=cholCoeff[pit->a][vit->a]*w;
    	}
    	unsigned short v = cNumPol[vit->a].b;

    	for(unsigned short i=vit->a;i<cNumPol.size();++i){
    		cNumPol[i].b-=v;
    	}
    }    
  }
  
  void Parameters::calcQtlGenEff(){
    for(unsigned short i;i<userQtlsEff.size();++i){
      for(unsigned short j;j<userQtlsEff[i].size();++j){
	qtlsGenEff[i][j]=sqrt((genAdCov[i][i]*userQtlsEff[i][j])/2*qtlsAlelleFreq[i][j]*(1-qtlsAlelleFreq[i][j]));
      }
    }
  }

    
  void Parameters::setChromQtls(){
    chromQtls.resize(numChrom);
    qtlPos.resize(userQtlsEff.size());
    unsigned long rNumber=0;
    double rNumber1=0;
    pair<unsigned short> qtlId;
    pair<double> qtlP;
    for(unsigned short i=0;i<userQtlsEff.size();++i){
      for(unsigned short j=0;j<userQtlsEff[i].size();++j){
	rNumber=gsl_rng_uniform_int(prand,numChrom);
	qtlId.a=i;                                           //Trait's identification
	qtlId.b=j;                                           //Qtl's identification
	chromQtls[rNumber].push_back(qtlId);
	//************************************************************	
	//Generating the position-BEGGINING                          *
	//************************************************************
	rNumber1=gsl_rng_uniform(prand)*rNumber;
	qtlP.a=(unsigned short)rNumber;
	qtlP.b=rNumber1;
	qtlPos[i].push_back(qtlP);
	//************************************************************	
	//Generating the position-END                                *
	//************************************************************
      }
    }
  }


  void Parameters::setSimType(){
    cout<<"Which simulation type would you like to use?"<<endl<<endl;
    cout<<"1. Gene level Simulation \t"<<"2. Individual level Simulation"<<endl;

    unsigned t=0;
    while(!(cin>>t)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
    }
    simType=t;
    cout<<cian<<"Simulation type chosen: "<<simType<<color_normal<<endl;
  }

  void Parameters::setSpecies(){
    
    cout<<"Please, provide the species you wish to simulate data: "<<"\n"<<"(If you select an species from the list below, the genome's size, the number of chromosome and the chromosome's size will be set automatically)"<<endl<<endl;
    
    cout<<"a. swine"<<"\t"<<"b. bovine"<<"\t"<<"c. ovine"<<endl;
    cout<<"d. poultry"<<"\t"<<"e. buffalo"<<"\t"<<"f. goats"<<endl;
    cout<<"g. horse"<<"\t"<<"h. customize species"<<endl<<endl;
    
    char option;
    cout<<"Option : "; 
    while(!(cin>>option)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid option: ";
    }
    switch( option ){
    case 'a':
    case 'A': 
      genomeSize=2800;
      numChrom=18;
      species="Swine";
      cout<<endl;
      cout<<cian<<"Swine selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl; 
      break;
    case 'b':
    case 'B':
      genomeSize=3000;
      numChrom=29;
      cout<<endl;
      species="Bovine";
      cout<<cian<<"Bovine selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;
    case 'c':
    case 'C':
      genomeSize=3000;
      numChrom=26;
      cout<<endl;
      species="Ovine";
      cout<<cian<<"Ovine selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;
    case 'd':
    case 'D':
      genomeSize=3800;
      numChrom=38;
      cout<<endl;
      species="Poultry";
      cout<<cian<<"Poultry selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;
    case 'e':
    case 'E':
      genomeSize=0;
      numChrom=24;
      species="Buffalo";
      cout<<endl;
      cout<<cian<<"Buffalo selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;
    case 'f':
    case 'F':
      genomeSize=3110;
      numChrom=29;
      species="Goats";
      cout<<endl;
      cout<<cian<<"Goats selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;    
    case 'g':
    case 'G':
      genomeSize=0;
      numChrom=31;
      species="Horse";
      cout<<endl;
      cout<<cian<<"Horse selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;    
    default:
      setGenomeSize();
      setNumChrom();
      break;
    }
  }
  void Parameters::setGenomeSize(){ 
    
    cout<<"Please, enter the genome's size (in cM): ";
    unsigned t=0;
    while(!(cin>>t)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
    }
    genomeSize=t;
    cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
    
  }
  void Parameters::setNumChrom(){
    
    unsigned t=0;
    cout<<"Please, enter the number of chromosomes in the genome: ";
    while(!(cin>>t)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
    }
    numChrom=t;
    cout<<cian<<"Number of Chromosomes loaded: "<<numChrom<<color_normal<<endl;
    
  } 
  void Parameters::setChromLoci(){
    int option;
    cout<<"Would you like to specify the number of loci per chromosome?"<<endl;
    cout<<"1. Yes"<<"\t"<<"2. No (in this case the loci will be randomly distributed)"<<endl;
    cout<<"Option : ";            
    while(!(cin>>option)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid option: ";
    }
    
    while(option!=1&&option!=2){
      cout<<"\nEnter a valid option: ";      
      while(!(cin>>option)){
	cin.clear();     
	while(cin.get()!='\n'){
	  continue;
	}
      }
    }
    
    if(option==1) {
      unsigned t=0;
      for(unsigned short c=0;c<numChrom;++c){
	cout<<"Enter the number of loci in the chromosome "<<c+1<<": ";
	while(!(cin>>t)){
	  cin.clear();
	  while(cin.get()!='\n'){
	    continue;
	  }
	  cout<<"Enter a valid number: ";
	}
	chromLoci.push_back(t);
	continue;
	
	cout<<"Loci loaded for chromosome "<<c+1<<": "<<chromLoci[c]<<endl;
      }
    }
    else {
      
      vector<pair<unsigned short> >::iterator pit=numPol.end()-1;
      unsigned lociCounter=0;
      chromLoci.resize(numChrom);
      for(unsigned short i=0;i<numChrom-1;++i){
	chromLoci[i]=unsigned(double(chromSizes[i])/double(genomeSize)*pit->b);
	lociCounter+=chromLoci[i];
      }
      chromLoci[numChrom-1]=pit->b-lociCounter;
      
    }
    for(unsigned short i=0;i<numChrom;++i){
      cout<<cian<<"Chromosome "<<i+1<<"' size is: "<<chromLoci[i]<<color_normal<<endl;
    }
  }
   
  
  void Parameters::setChromSizes() {
    char option;
    cout<<"Would you like to specify the chromosomes' sizes?"<<endl;
    cout<<"Y. Yes"<<"\t"<<"N. No (in this case the sizes will be randomly generated)"<<endl;
    cout<<"Option : ";       
    while(!(cin>>option)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid option: ";
    }
    
    while(option!='n'&&option!='y'){
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid option: ";
    }
    
    if(option=='y'){
      unsigned t=0;
      for(unsigned short c=0;c<numChrom;++c){
	cout<<"Enter the size of chromosome "<<c+1<<": ";
	while(!(cin>>t)){
	  cin.clear();
	  while(cin.get()!='\n'){
	    continue;
	  }
	  cout<<"Enter a valid size: ";
	}
	chromSizes.push_back(t);
	continue;
	
	cout<<"Size loaded: "<<chromSizes[c]<<endl;
      }
    }
    
    else{
      
      vector<unsigned> temp;
      
      temp.push_back(0);
      temp.push_back(genomeSize);    
      
      vector<unsigned>::iterator it;
      unsigned long n=0;
      for (unsigned short i=0; i<numChrom-1; ++i){
	n=gsl_rng_uniform_int(prand,genomeSize+1);
	it=find(temp.begin(),temp.end(),n);	
	if (it==temp.end())
	  {
	    temp.push_back(n);
	  }
	else 
	  {
	    --i;
	  }

      }
      
      sort(temp.begin(), temp.end());
      
      for(unsigned short i=0;i<numChrom;++i){
	chromSizes.push_back(temp[i+1]-temp[i]);
      }
      for(unsigned short i=0;i<numChrom;++i){
	cout<<cian<<"Chromosome "<<i+1<<"' size is: "<<chromSizes[i]<<color_normal<<endl;
      }
    }
  } 

  void Parameters::setRecombRate(){
    cout<<"Enter a recombination rate: ";
    double d=0.0;
    while(!(cin>>d)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"\nEnter a valid number: ";
    }
    recombRate=d;
    cout<<endl;
    cout<<cian<<"Recombination rate loaded: "<<recombRate<<color_normal<<endl;        
  }
   
  void Parameters::setMarkerDist() {
    unsigned short option;
    cout<<"Would you like to generate markers?"<<endl;
    cout<<"1. Yes (set same distance for all chromosomes)"<<"\t"<<"2. Yes (set different distance for each chromosome)"<<"\t"<<"3. No"<<endl;
    cout<<"Option : ";
    while(!(cin>>option)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid option: ";
    }
    double d=0.0;
    switch (option){
    case 1:
      cout<<"Enter the distance between the markers (cM): ";
         while(!(cin>>d)){
	cin.clear();
	while(cin.get()!='\n'){
	  continue;
	}
	cout<<"Enter a valid option: ";
      }
	 markerDist=d;
      cout<<cian<<"Marker distance loaded: "<<markerDist<<color_normal<<endl;
      break;
      
    case 2:
      setMarkerChrom();
       break;
      
    case 3: 
      cout<<"None markers generated!"<<endl;
      break;
    }
  }
   
  void Parameters::setMarkerChrom(){
        double t=0;
      for(unsigned short c=0;c<numChrom;++c){
	cout<<"Enter the distance between markers on chromosome "<<c+1<<": ";
	while(!(cin>>t)){
	  cin.clear();
	  while(cin.get()!='\n'){
	    continue;
	  }
	  cout<<"Enter a valid size: ";
	}
	markerChrom.push_back(t);
	
	cout<<cian<<"Marker distance loaded on chromosome "<<c+1<<": "<<markerChrom[c]<<color_normal<<endl;
      }
    } 
  

   
  void Parameters::setNumTraits(){
    
    cout<<"Please, provide number of traits to be simulated: ";
    unsigned short u=0;
    while(!(cin>>u)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: "; 
    }
    while(u==0){               // Proteção para 0.
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
      cin>>u;
    }
    numTraits=u;
    
    cout<<cian<<"Number of traits loaded: "<<numTraits<<color_normal<<endl;    
  }
  void Parameters::setNumPol(){
    
    numPol.resize(numTraits);
    unsigned short u=0;
    cout<<"Please, insert the traits in"<<red<<" crescent order"<<color_normal<<" of Poligenic's Locus"<<endl;
    for(unsigned short i=0;i<numTraits;++i){
      cout<<"Enter trait "<<i+1<<"'s number of polygenic loci: ";
      while(!(cin>>u)){
	cin.clear();
	while(cin.get()!='\n'){
	  continue;
	}
	cout<<"Enter a valid number: ";
      }
      while(u==0){               // Proteção para 0.
	cin.clear();
	while(cin.get()!='\n'){
	  continue;
	}
	cout<<"Enter a valid number: ";
	cin>>u;
      }

      numPol[i].b=u;
      numPol[i].a=i;
      
      cout<<cian<<"Trait "<<i+1<<"'s number of polygenic loci loaded: "<<numPol[i].b<<color_normal<<endl;          
    }
  }
  void Parameters::setFreqAlelle(){
    
    freqAlelle.resize(numTraits);
    double d=0.0;
    for(unsigned short i=0;i<numTraits;++i){
      cout<<"Provide the alelle A1's relative frequency for trait "<<i+1<<": ";
      while(!(cin>>d)){
	cin.clear();
	while(cin.get()!='\n'){
	  continue;
	}
	cout<<"Enter a valid number: ";
      }
      while(d<=0){               // Proteção para 0 e numeros negativos.
	cin.clear();
	while(cin.get()!='\n'){
	  continue;
	}
	cout<<"Enter a valid number: ";
	cin>>d;
      }

      freqAlelle[i]=d;
      cout<<cian<<"Alelle Frequency loaded of "<<i+1<<"'s trait: "<<freqAlelle[i]<<color_normal<<endl;
    }
  }
  
  void Parameters::setNumQtls() {
    unsigned short u=0;
    vector<unsigned short> nqtl(numTraits);
    for(unsigned short i=0;i<numTraits;++i){
      cout<<"Enter trait "<<i+1<<"'s number of Qtls: ";
      while(!(cin>>u)){
	cin.clear();
	while(cin.get()!='\n'){
	  continue;
	}
	cout<<"Enter a valid number: ";
      }
      nqtl[i]=u;      
      cout<<cian<<"Number of Qtls loaded for trait "<<i+1<<": "<<nqtl[i]<<color_normal<<endl;
    }
    
    
    //****************************************************************
    //Resizing Qtls related Matrices-BEGINNING                       *
    //****************************************************************
    userQtlsEff.resize(numTraits);
    for(unsigned short i=0;i<numTraits;++i){
      userQtlsEff[i].resize(nqtl[i]);
    }
    
    qtlsGenEff.resize(numTraits);
    for(unsigned short i=0;i<numTraits;++i){
      qtlsGenEff[i].resize(nqtl[i]);
    }
    
    qtlsAlelleFreq.resize(numTraits);
    for(unsigned short i=0;i<numTraits;++i){
      qtlsAlelleFreq[i].resize(nqtl[i]);
    }    
    //****************************************************************
    //Resizing Qtls related Matrices-END                             *
    //****************************************************************  
  
  }
  void Parameters::setFreqQtls(){
    double d=0.0;
    vector<unsigned short> nqtl(numTraits);
    for(unsigned short i=0;i<numTraits;++i){      
      for(unsigned short j=0;j<nqtl[i];++j){
	cout<<"Enter the Qtl "<<j+1<<"'s relative frequency of the alelle A1 for the trait "<<i+1<<":";
	while(!(cin>>d)){
	  cin.clear();
	  while(cin.get()!='\n'){
	    continue;
	  }
	  cout<<"\nEnter a valid number: ";
	}
	while(d<=0){               // Proteção para 0 e numeros negativos.
	  cin.clear();
	  while(!(cin>>d)){
	    cin.clear();
	    while(cin.get()!='\n'){
	      continue;
	    }
	    cout<<"\nEnter a valid number: ";
	  }
	}
	qtlsAlelleFreq[i][j]=d;
	cout<<endl;
	cout<<cian<<"Alelle A1's frequency loaded: "<<qtlsAlelleFreq[i][j]<<color_normal<<endl;
      }
    }
  }
  
  void Parameters::setEffQtls(){
    double d=0.0;
    vector<unsigned short> nqtl(numTraits);
    for(unsigned short i=0;i<numTraits;++i){      
      for(unsigned short j=0;j<nqtl[i];++j){
	cout<<"Enter the Qtl "<<j+1<<"'s relative effect (as a percentage of the additive genetic variance) for the trait "<<i+1<<":";
	while(!(cin>>d)){
	  cin.clear();
	  while(cin.get()!='\n'){
	    continue;
	  }
	  cout<<"\nEnter a valid number: ";
	}
	while(d<=0&&d>1){               // Proteção para 0 e numeros negativos.
	  cin.clear();
	  while(!(cin>>d)){
	    cin.clear();
	    while(cin.get()!='\n'){
	      continue;
	    }
	    cout<<"\nEnter a valid number: ";
	  }
	}
	userQtlsEff[i][j]=d;
	cout<<endl;
	cout<<cian<<"Alelle A1's relative effect loaded: "<<userQtlsEff[i][j]<<color_normal<<endl;
      }
    }
  }
  
  void Parameters::setPosQtls(){
    char option;
    cout<<"Would you like to specify in which chromosomes the Qtls are located?"<<endl;
    cout<<"Y. Yes"<<"\t"<<"N. No (in this case the Qtls will be randomly allocated to chromosomes)"<<endl;
    cout<<"Option : ";       
    while(!(cin>>option)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid option: ";
    }
    
    while(option!='n'&&option!='y'){
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid option: ";
    }
    
    if(option=='y'){
      chromQtls.resize(numChrom);
      qtlPos.resize(userQtlsEff.size());
      pair<unsigned short> qtlId;
      pair<double> qtlP;
      for(unsigned short i=0;i<userQtlsEff.size();++i){
	for(unsigned short j=0;j<userQtlsEff[i].size();++j){
	  cout<<"In which chromosome the Qtl "<<j+1<<" of trait "<<i+1<<" should be allocated? (number of chromosome:"<<numChrom<<")  :";
	  unsigned short u=0;	  
	  while(!(cin>>u)){
	    cin.clear();
	    while(cin.get()!='\n'){
	      continue;
	    }
	    cout<<"Enter a valid number: ";
	  }
	  qtlId.a=i;                                           //Trait's identification
	  qtlId.b=j;                                           //Qtl's identification
	  chromQtls[u-1].push_back(qtlId);
	  while(cin.get()!='\n'){                              //In the case a float-point number has been entered in u
	    continue;
	  }
	  cout<<cian<<"Chromosome selected: "<<u<<color_normal<<endl;
	  double d=0.0;
	  cout<<"In which position (cM) you would like to allocate this Qtl? (Lenght of the chromosome "<<u<<": "<<chromSizes[u-1]<<"): ";
	  while(!(cin>>d)&&d<0){
	    cin.clear();
	    while(cin.get()!='\n'){
	      continue;
	    }
	    cout<<"Enter a valid number: ";
	  }
	  qtlP.a=(short unsigned)(u-1);
	  qtlP.b=d;
	  qtlPos[i].push_back(qtlP);
	  cout<<cian<<"Position loaded: "<<qtlPos[i][j].b<<color_normal<<endl;
	}
      }	
    }
    else{
      setChromQtls();
    } 
  }
  void Parameters::setHeritability(){
    
    heritability.resize(numTraits);
    double d=0.0;
    for(unsigned short i=0;i<numTraits;++i){
      cout<<"Enter trait "<<i+1<<"'s heritability: ";
      while(!(cin>>d)){
	cin.clear();
	while(cin.get()!='\n'){
	  continue;
	}
	cout<<"Enter a valid number: ";
      }
      while(d<=0){               // Proteção para 0 e numeros negativos.
	cin.clear();
	while(cin.get()!='\n'){
	  continue;
	}
	cout<<"Enter a valid number: ";
	cin>>d;
      }

      heritability[i]=d; 
      cout<<cian<<"Heritability loaded of "<<i+1<<"'s trait: "<<heritability[i]<<color_normal<<endl;
    }
  }
  
  void Parameters::setTraitMeans(){
    traitMeans.resize(numTraits);
    double d=0.0;
    for(unsigned short i=0;i<numTraits;++i){
      cout<<"Provide the trait "<<i+1<<"' mean: ";
      while(!(cin>>d )){
	cin.clear();
	while(cin.get()!='\n'){
	  continue;
	}
	cout<<"\nEnter a valid number: ";
      }
      traitMeans[i]=d;

      cout<<cian<<"Trait mean loaded of "<<i+1<<"'s trait: "<<traitMeans[i]<<color_normal<<endl;
    }    
  }
  
  void Parameters::setGenAdCov(){
    
    //-----Resizing----BEGIN----   
    genAdCov.resize(numTraits);
    for(unsigned short i=0;i<numTraits;++i){
      genAdCov[i].resize(numTraits);
    }
    //-----Resizing----END------
    double d=0.0;
    for(unsigned short i=0;i<numTraits;++i){
      cout<<"Enter the trait "<<i+1<<"'s genetic additive variance: ";
      while(!(cin>>d)){
	cin.clear();
	while(cin.get()!='\n'){
	  continue;
	}
	cout<<"Enter a valid number: ";
      }
      genAdCov[i][i]=d;

      cout<<cian<<"Additive genetic variance loaded of "<<i+1<<"'s trait: "<<genAdCov[i][i]<<color_normal<<endl;
    }
  }
  void Parameters::setGenAdCorr(){
    //-----Resizing----BEGIN----   
    genAdCorr.resize(numTraits);
    for(unsigned short i=0;i<numTraits;++i){
      genAdCorr[i].resize(numTraits);
    }
    //-----Resizing----END------ 
    double d=0.0;
    for(unsigned short i=0;i<numTraits;++i){
      genAdCorr[i][i]=1;
      cout<<cian<<"Additive genetic correlation of "<<i+1<<"'s trait: "<<genAdCorr[i][i]<<color_normal<<endl;
      for(unsigned short j=0;j<i;++j){
	cout<<"Enter the additive genetic correlation between traits "<<i+1<<" and "<<j+1<<" :";
	while(!(cin>>d)){
	  cin.clear();
	  while(cin.get()!='\n'){
	    continue;
	  }
	  cout<<"Enter a valid number: ";
	}
	genAdCorr[i][j]=d;
	cout<<cian<<"Additive genetic correlation loaded between traits "<<i+1<<"'s and "<<j+1<<"'s trait: "<<genAdCorr[i][j]<<color_normal<<endl;
	genAdCorr[j][i]=d;
	cout<<cian<<"Additive genetic covariance loaded of "<<i+1<<"'s trait: "<<genAdCov[i][j]<<color_normal<<endl;
      }
    }
  }
  void Parameters::setBasePopSize(){
    
    cout<<"Provide the base-population's size: ";
    unsigned long ul=0;
    while(!(cin>>ul)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
    }
    while(ul==0){               // Proteção para 0 
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
      cin>>ul;
    }
    
    basePopSize=ul;
    cout<<cian<<"Base-population size loaded: "<<basePopSize<<color_normal<<endl; 
  }
  void Parameters::setNumGen(){
    
    unsigned u=0;
    cout<<"Provide the number of generations: ";    
    while(!(cin>>u)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
    }
    while(u==0){               // Proteção para 0.
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
      cin>>u;
    }
    
    numGen=u;
    
    cout<<cian<<"Number of generations loaded: "<<numGen<<color_normal<<endl;
  }
  void Parameters::setNumMale(){
    
    unsigned long ul=0;
    cout<<"Provide the number of males to be selected: ";
    while(!(cin>>ul)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
    } 
    while(ul==0){           // Proteção para 0
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
      cin>>ul;
    }
    numMale=ul;
    
    cout<<cian<<"Number of Males loaded: "<<numMale<<color_normal<<endl;
    
  }
  void Parameters::setNumFem(){
    
    unsigned long ul=0;
    cout<<"Provide the number of females to be selected: ";
    while(!(cin>>ul)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
    }
    while(ul==0){           // Proteção para 0
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
      cin>>ul;
    }
    
    numFem=ul/numMale;
    
    cout<<cian<<"Number of females loaded: "<<ul<<color_normal<<endl;
    cout<<cian<<"Number of females per male: "<<numFem<<color_normal<<endl;
  }
  void Parameters::setNumOff(){
    
    unsigned long ul=0;
    cout<<"Provide the number of offspring per mate: ";
    while(!(cin>>ul)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
    }
    while(ul==0){           // Proteção para 0
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
      cin>>ul;
    }
    
    numOff=ul;  
    
    cout<<cian<<"Number of offspring per mate loaded: "<<numOff<<color_normal<<endl;
  }

  void Parameters::setSelMethod(){
	  cout<<"Would you like to select for more than one trait?"<<endl;
	  cout<<"a. yes"<<"\t"<<"b. no"<<endl;
	  char option;

	  while(!(cin>>option)){
		  cin.clear();
		  while(cin.get()!='\n'){
			  continue;
		  }
		  cout<<"Enter a valid option: ";
		  cin>>option;
	  }
	  if(option='a'){
		  cout<<"Which selection method you would like to use?"<<endl;
		  cout<<"a. tandem"<<"\t"<<"b. independent levels"<<"\t"<<"c. selection Index"<<endl;
		  cin>>option;

		  switch(option){
		  case 'a': {cout<<"Provide the changing trait criterion (genetic gains or number of generations):"<<endl;
		  double chcrit=0;
		  for(int i=0;i<numTraits;++i){
			  cout<<"Criterion for trait "<<i+1<<": ";
			  cin>>chcrit;
			  vcc.push_back(chcrit);
		  }
		  cout<<"Would like to provide the trait's economic values? (If no, equal economic values will be assigned to all traits)"<<endl;
		  cout<<"a. yes\t"<<"b. no"<<endl;
		  while(!(cin>>option)){
			  cin.clear();
			  while(cin.get()!='\n'){
				  continue;
			  }
			  cout<<"Enter a valid option: ";
			  cin>>option;
		  }
		  if(option=='a'){
			  double ec=0;
			  cout<<"Provide the economic values for the traits:"<<endl;
			  for(int i=0;i<numTraits;++i){
				  cout<<"Economic value for trait "<<i+1<<": ";
				  cin>>ec;
				  vec.push_back(ec);
			  }
		  }
		  }
		  break;
		  case 'b': cout<<"Provide information for independent levels selection method. (Not implemented yet)."<<endl;
		  break;
		  case 'c': cout<<"Provide information for selection Index method. (Not implemented yet)."<<endl;
		  }
	  }
  }

  void Parameters::setRep(){
    unsigned u=0;
    cout<<"Provide the number of replicates (This number determines how many times the simulation will be replicate for the same set of parameters): ";
    while(!(cin>>u)){
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
    }
    while(u==0){           // Proteção para 0
      cin.clear();
      while(cin.get()!='\n'){
	continue;
      }
      cout<<"Enter a valid number: ";
      cin>>u;
    }
    rep=u;
    cout<<cian<<"Number of replicates loaded: "<<rep<<color_normal<<endl;
    
  }
  
  vector<double> Parameters::getVcc(){
	  vector<double> temp(0,vec.size());
	  temp=vcc;
	  return temp;
  }

  vector<double> Parameters::getVec(){
  	  vector<double> temp(0,vec.size());
  	  temp=vec;
  	  return temp;
    }

  void Parameters::input(){
    
    cout<<"Welcome to the LZ5's interactive input mode!"<<endl;
    cout<<"(To quit the input mode, press Ctrl+c)"<<endl<<endl; 
    
    cout<<"****************************************************************"<<endl;
    cout<<"Choosing the Simulation Type                                   *"<<endl;
    cout<<"****************************************************************"<<endl;
    
    setSimType();
    if(simType==1){
    cout<<"****************************************************************"<<endl;
    cout<<"Setting Genome Parameters:                                     *"<<endl;
    cout<<"****************************************************************"<<endl;
    
    setSpecies();
    setChromSizes();
    setRecombRate();    
    setMarkerDist();
    
    
    
    cout<<"****************************************************************"<<endl;
    cout<<"Setting Trait's Parameters:                                    *"<<endl;
    cout<<"****************************************************************"<<endl;
    
    setNumTraits();
    setNumPol();
    setChromLoci();
    setFreqAlelle();
    setNumQtls();
    setFreqQtls();
    setEffQtls();
    setPosQtls();
    setHeritability();
    setTraitMeans();
    setGenAdCov();
    setGenAdCorr(); 
    
    cout<<"****************************************************************"<<endl;
    cout<<"Setting Population Parameters:                                 *"<<endl;
    cout<<"****************************************************************"<<endl;
    
    setBasePopSize();
    setNumGen();
    
    cout<<"****************************************************************"<<endl;
    cout<<"Setting Selection Parameters:                                  *"<<endl;
    cout<<"****************************************************************"<<endl;
    
    setNumMale();
    setNumFem();
    setNumOff();
    setSelMethod();
    
    cout<<"****************************************************************"<<endl;
    cout<<"Setting Replicates:                                            *"<<endl;
    cout<<"****************************************************************"<<endl;
    
    setRep();
    }
    else{
      cout<<"****************************************************************"<<endl;
      cout<<"Setting Trait's Parameters:                                    *"<<endl;
      cout<<"****************************************************************"<<endl;
      
      setNumTraits();
      setHeritability();
      setTraitMeans();
      setGenAdCov();
      setGenAdCorr();
      
      cout<<"****************************************************************"<<endl;
      cout<<"Setting Population Parameters:                                 *"<<endl;
      cout<<"****************************************************************"<<endl;
      
      setBasePopSize();
      setNumGen();
      
      cout<<"****************************************************************"<<endl;
      cout<<"Setting Selection Parameters:                                  *"<<endl;
      cout<<"****************************************************************"<<endl;
      
      setNumMale();
      setNumFem();
      setNumOff();
      
      cout<<"****************************************************************"<<endl;
      cout<<"Setting Replicates:                                            *"<<endl;
      cout<<"****************************************************************"<<endl;
      
      setRep();
    }
    cout<<endl<<endl;
    cout<<cian<<"Finally!!"<<color_normal<<endl<<endl;
  }

  // Começo da programação da Interface de Comando.

  void Parameters::setSpecies(string s, double r, unsigned t){// Essa função é para setar especie(genoma,cromossomo e tamanho do cromossomo) e taxa de recombinaçao!
  

 char option;
    
    recombRate=r;
    species=s;

    if(s=="swine"){option = 'a';} 
    else if(s=="bovine"){option='b';}
    else if(s=="ovine"){option='c';}
    else if(s=="poultry"){option='d';}
    else if(s=="buffalo"){option='e';}
    else if(s=="goats"){option='f';}
    else if(s=="horse"){option='g';}
    else {option='h';}

 switch( option ){
    case 'a':
    case 'A': 
      genomeSize=2800;
      numChrom=18;
      cout<<endl;
      cout<<cian<<"Swine selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl; 
      break;
    case 'b':
    case 'B':
      genomeSize=3000;
      numChrom=29;
      cout<<endl;
      cout<<cian<<"Bovine selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;
    case 'c':
    case 'C':
      genomeSize=3000;
      numChrom=26;
      cout<<endl;
      cout<<cian<<"Ovine selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;
 case 'd':
    case 'D':
      genomeSize=3800;
      numChrom=38;
      cout<<endl;
      cout<<cian<<"Poultry selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;
    case 'e':
    case 'E':
      genomeSize=0;
      numChrom=24;
      cout<<endl;
      cout<<cian<<"Buffalo selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;
    case 'f':
    case 'F':
      genomeSize=3110;
      numChrom=29;
      cout<<endl;
      cout<<cian<<"Goats selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;
 case 'g':
    case 'G':
      genomeSize=0;
      numChrom=31;
      cout<<endl;
      cout<<cian<<"Horse selected!"<<color_normal<<endl;
      cout<<cian<<"Genome Size loaded: "<<genomeSize<<color_normal<<endl;
      cout<<cian<<"Number of chromosome's pair loaded: "<<numChrom<<" (sexual chromosome will not be considered)"<<color_normal<<endl;
      break;    
    default:
      cout<< "Please, use a valid name!"<<endl;
      break;
    }

 if (t==0){
      vector<unsigned> temp;
      
      temp.push_back(0);
      temp.push_back(genomeSize);    
      
      vector<unsigned>::iterator it;
      unsigned long n=0;
      for (unsigned short i=0; i<numChrom-1; ++i){
	n=gsl_rng_uniform_int(prand,genomeSize+1);
	it=find(temp.begin(),temp.end(),n);	
	if (it==temp.end())
	  {
	    temp.push_back(n);
	  }
	else 
	  {
	    --i;
	  }
	
      }
      
      sort(temp.begin(), temp.end());
      
      for(unsigned short i=0;i<numChrom;++i){
	chromSizes.push_back(temp[i+1]-temp[i]);
      }
     }
     cout<<cian<<"Recombination Rate Loaded: "<<recombRate<<color_normal<<endl;    
     for(unsigned short i=0;i<numChrom;++i){
      cout<<cian<<"Chromosome "<<i+1<<"' size is: "<<chromSizes[i]<<color_normal<<endl;
     }
  }
  void Parameters::setGenome(unsigned g, unsigned c, double r, unsigned t){
    
    genomeSize=g;
    numChrom=c;
    recombRate=r;
    
    if (t==0){
      vector<unsigned> temp;
      
      temp.push_back(0);
      temp.push_back(genomeSize);    
      
      vector<unsigned>::iterator it;
      unsigned long n=0;
      for (unsigned short i=0; i<numChrom-1; ++i){
	n=gsl_rng_uniform_int(prand,genomeSize+1);
	it=find(temp.begin(),temp.end(),n);	
	if (it==temp.end())
	  {
	    temp.push_back(n);
	  }
	else 
	  {
	    --i;
	  }
	
      }
      
      sort(temp.begin(), temp.end());
      
      for(unsigned short i=0;i<numChrom;++i){
	chromSizes.push_back(temp[i+1]-temp[i]);
      }
    }
    cout<<cian<<"Genome's Size: "<<genomeSize<<color_normal<<endl;
    cout<<cian<<"Number of Cromossomos: "<<numChrom<<color_normal<<endl;
    cout<<cian<<" Recombination's Rate: "<<recombRate<<color_normal<<endl;
    for(unsigned short i=0;i<numChrom;++i){
      cout<<cian<<"Chromosome "<<i+1<<"' size is: "<<chromSizes[i]<<color_normal<<endl;
    }
  }
 void Parameters::setMarker(unsigned m){
    markerDist=m;
    cout<<cian<<"Marker distance loaded: "<<markerDist<<color_normal<<endl;
    //Falta o Arquivo externo!
  }
  
  void Parameters::setTrait(short t, short l, double f, int q){
    
    if(t>freqAlelle.size()) {
    numPol.resize(t);
    freqAlelle.resize(t);  
    }

    numPol[t-1].a=t-1;
    numPol[t-1].b=l;
    freqAlelle[t-1]=f;

    if(q==0){
      vector<pair<unsigned short> >::iterator pit=numPol.end()-1;
      unsigned lociCounter=0;
      chromLoci.resize(numChrom);
      for(unsigned short i=0;i<numChrom-1;++i){
	chromLoci[i]=unsigned(double(chromSizes[i])/double(genomeSize)*pit->b);
	lociCounter+=chromLoci[i];
      }
      chromLoci[numChrom-1]=pit->b-lociCounter;
    }
   
   
      cout<<cian<<"Numero de Locos Poligenico da Caracteristica "<<t<<": "<<numPol[t-1].b<<color_normal<<endl;
      cout<<cian<<"Frequencia de Alelos da Caracteristica "<<t<<": "<<freqAlelle[t-1]<<color_normal<<endl;
      numTraits=freqAlelle.size();
  }

  void Parameters::setQtls(unsigned t, unsigned q, short c, short p, double f, double e){
    
    if(t>qtlsAlelleFreq.size()){
      
      qtlPos.resize(t);
      qtlsAlelleFreq.resize(t);
      userQtlsEff.resize(t);
           
      pair<double> u;
      u.a=c;
      u.b=p;
      
      qtlPos[t-1].push_back(u);
      qtlsAlelleFreq[t-1].push_back(f);
      userQtlsEff[t-1].push_back(e);
    }   
    
    
    else if(q>qtlsAlelleFreq[t-1].size()){
      if(t==1){
     for(unsigned short i=0;i<t;++i){
	  qtlPos[i].resize(q);
	  qtlsAlelleFreq[i].resize(q);
	  userQtlsEff[i].resize(q);
	}
    }
      else if(t==2){
	for(unsigned short i=1;i<t;++i){
	  qtlPos[i].resize(q);
	  qtlsAlelleFreq[i].resize(q);
	  userQtlsEff[i].resize(q);
	}
      }
      else if(t==3){
	for(unsigned short i=2;i<t;++i){
	  qtlPos[i].resize(q);
	  qtlsAlelleFreq[i].resize(q);
	  userQtlsEff[i].resize(q);
	}
      }
      else if(t==4){
	for(unsigned short i=3;i<t;++i){
	  qtlPos[i].resize(q);
	  qtlsAlelleFreq[i].resize(q);
	  userQtlsEff[i].resize(q);
	}
      }
    }
    
    qtlPos[t-1][q-1].a=c;
    qtlPos[t-1][q-1].b=p;
    
    qtlsAlelleFreq[t-1][q-1]=f;
    
    userQtlsEff[t-1][q-1]=e;
    
     for(int i=0;i<qtlPos.size();i++){
       for(int j=0;j<qtlPos[i].size();j++){
	 
	 cout<<"qtlpos["<<i<<"]["<<j<<"] é: "<<qtlPos[i][j].a<<qtlPos[i][j].b<<endl;
	 
       }
     }
     
     cout<<cian<<"Posição do Qtl no chromossomo "<<qtlPos[t-1][q-1].a<<": "<<qtlPos[t-1][q-1].b<<color_normal<<endl;
     cout<<cian<<"A Frequencia do Qtl: "<<qtlsAlelleFreq[t-1][q-1]<<color_normal<<endl;
     cout<<cian<<"E o Efeito em % : "<<userQtlsEff[t-1][q-1]<<color_normal<<endl;
        
  }
  
  void Parameters::setParTrait(unsigned t, double h, double m, double vg) {
    
    if(t>heritability.size()){
      heritability.resize(t);
      traitMeans.resize(t);
    }
    heritability[t-1]=h;
    traitMeans[t-1]=m;
    
    int j= heritability.size();
    
    //-----Resizing----BEGIN----   
    genAdCov.resize(j);
    for(unsigned short i=0;i<j;++i){
      genAdCov[i].resize(j);
    }
    //-----Resizing----END------
    
    
    genAdCov[t-1][t-1]=vg;
    
    
    
    cout<<cian<<"Herdabilidade: "<<heritability[t-1]<<color_normal<<endl;
    cout<<cian<<"Trait means: "<<traitMeans[t-1]<<color_normal<<endl; 
    cout<<cian<<"Variância Genética Aditiva: "<<genAdCov[t-1][t-1]<<color_normal<<endl;
  
}

 void Parameters::setCorr(unsigned a, unsigned b, double c){ 
    
    int j= freqAlelle.size();

    genAdCorr.resize(j);
    for(unsigned short i=0;i<j;++i){
      genAdCorr[i].resize(j);
    }  
    
    genAdCorr[a-1][b-1]=c;
    genAdCorr[b-1][a-1]=c;
    
    for(int i=0;i<j;++i){
      for(int m=0;m<j;++m){
	genAdCorr[i][i]=1;
	cout<<"\t["<<i<<"] ["<<m<<"] :"<<genAdCorr[i][m];
      }
    }
 }
    

  void Parameters::exec(lz5_Result_Struct& e) {    
    if(e.object!=getName()){return;}
    if(e.method=="input"){
      input();
      calcAdCov();
      if(simType==1){
	adjAdVar();
	calcPolVal();
	calcQtlGenEff();
      }
    }
    else if(e.method=="setSpecies") {setSpecies(e._string[0],e._double[0], e._unsigned[0]);}
    else if(e.method=="setGenome") {setGenome(e._unsigned[0],e._unsigned[1],e._double[0],e._unsigned[2]);}   
    else if(e.method=="setMarker") {setMarker(e._unsigned[0]);}
    else if(e.method=="setTrait") {setTrait(e._unsignedShort[0],e._unsignedShort[1],e._double[0],e._int[0]);}
    else if(e.method=="setQtls") {setQtls(e._unsigned[0],e._unsigned[1],e._unsignedShort[0],e._unsignedShort[1],e._double[0],e._double[1]);}
    else if(e.method=="setParTrait") {setParTrait(e._unsigned[0],e._double[0],e._double[1],e._double[2]);}
    else if(e.method=="setCorr") {setCorr(e._unsigned[0],e._unsigned[1],e._double[0]);}
    else if(e.method=="calcAdCov"){calcAdCov();}
    else if(e.method=="adjAdVar"){adjAdVar();}
    else if(e.method=="calcPolVal"){calcPolVal();}    
    else if(e.method=="calcQtlGenEff"){calcQtlGenEff();}

  }
  
}


