#include<string.h>
#include<vector>
#include<algorithm>
#include"Lz5_Interpreter.h"

using std::string;
using std::vector;
using std::find;

namespace lz5
{
   
  void Lz5_Interpreter::cut(string param, lz5_Result_Struct& R, string& c){
    string arg=""; 
    vector<string> args;
    try
      {
	string::size_type loc = c.find( "...", 0 );
	if (loc == string::npos){	
	  for (unsigned i=0;i<c.size();i++)	   
	    {
	      if ((c.substr(i,1)==",")||(c.substr(i,1)==")"))
		{	
		  c.erase(0,arg.size()+1);		
		  break;
		}
	      arg+=c.substr(i,1);
	    }
	  if(param=="int"){	  
	    R._int.push_back(atoi(arg.c_str()));
	  }else if(param=="float"){	
	    R._float.push_back(float(atof(arg.c_str())));
	  }else if(param=="double"){
	    R._double.push_back(atof(arg.c_str()));
	  }else if(param=="string"){
	    R._string.push_back(arg);
	  }else if(param=="char"){
	    R._char.push_back(arg[0]);
	  }else if(param=="unsignedShort"){
	    R._unsignedShort.push_back((unsigned short)atoi(arg.c_str()));
	  }else if(param=="unsignedLong"){
	    R._unsignedLong.push_back((unsigned long)atol(arg.c_str()));
	  }else if(param=="unsigned"){
	    R._unsigned.push_back((unsigned)atoi(arg.c_str()));
	  }else if(param=="bool"){
	    bool flag=false;
	    if(arg=="true"){
	      flag=true;	      
	    }
	    R._bool.push_back(flag);
	  }
	}
	else{
	  for (unsigned i=0;i<c.size();i++)
	    {
	      if ((c.substr(i,1)==",")||(c.substr(i,1)==")"))
		{	   
		  args.push_back(arg);
		  c.erase(0,arg.length());
		  arg="";
		}
	      else{
		arg+=c.substr(i,1);
	      }
	    }
	  if(param=="int..."){
	    vector<int> t;
	    for(unsigned i=0; i< args.size(); i++){
	      string m=args[i];
	      t.push_back(atoi(m.c_str()));
	    }
	    R.__int.push_back(t);
	  }else if(param=="float..."){	
	    vector<float> t;
	    for(unsigned i=0; i< args.size(); i++){
	      string m=args[i];
	      t.push_back(float(atof(m.c_str())));
	    }
	    R.__float.push_back(t);
	  }else if(param=="double..."){
	    vector<double> t;
	    for(unsigned i=0; i< args.size(); i++){
	      string m=args[i];
	      t.push_back(atof(m.c_str()));
	    }
	    R.__double.push_back(t);
	  }else if(param=="string..."){
	    vector<string> t;
	    for(unsigned i=0; i< args.size(); i++){
	      t.push_back(args[i]);
	    }
	    R.__string.push_back(t);
	  }else if(param=="char..."){
	    vector<char> t;
	    for(unsigned i=0; i< args.size(); i++){
	      string m=args[i];
	      t.push_back(args[i][0]);
	    }
	    R.__char.push_back(t);
	  }else if(param=="unsignedShort..."){
	    vector<unsigned short> t;
	    for(unsigned i=0; i< args.size(); i++){
	      string m=args[i];
	      t.push_back((unsigned short)atoi(m.c_str()));
	    }
	    R.__unsignedShort.push_back(t);
	  }else if(param=="unsignedLong..."){
	    vector<unsigned long> t;
	    for(unsigned i=0; i< args.size(); i++){
	      string m=args[i];
	      t.push_back((unsigned long)atoi(m.c_str()));
	    }
	    R.__unsignedLong.push_back(t);
	  }else if(param=="unsigned..."){
	    vector<unsigned> t;
	    for(unsigned i=0; i< args.size(); i++){
	      string m=args[i];
	      t.push_back((unsigned)atoi(m.c_str()));
	    }
	    R.__unsigned.push_back(t);
	  }	  	
	}
      }
  catch( char * str )
    {
      std::cout << std::endl << "# Type mismatch: " << str << std::endl;      
    } 
  }

  
  lz5_Result_Struct Lz5_Interpreter::verify(string c){  
    lz5_Result_Struct R; 
    string comandos=c;
    
    for(unsigned i=0;i<=comandos.length();i++)
      {
	if ((comandos.substr(i,1)==" "))	
	  comandos=comandos.erase(i,1);
      }
    
    size_t num=comandos.find("(",0);
    
    if (num>=0){
      R.method=comandos.substr(0,num);
      comandos=comandos.erase(0,num+1);
    }else{
      R.method=comandos;
      comandos="";
    } 
    
    short pont=command.seek(R.method);
    
    if(pont>=0){
      R.object=command.get_object(pont);
      for(unsigned i=0; i<command.get_parameters_size(pont); i++){      
	cut(command.get_parameters(pont, i), R, comandos);
      }
    }
    else{
      clear(R);
    }
    return R;
  }

 
 void Lz5_Interpreter::readcomm(const char* f){
    std::FILE *fin=fopen(f, "r"); 
    bool aspas=false;
    if(fin!=NULL){
      vector<string> args;
      char linha[255];
      string str;
      while(!feof(fin)){      	
	fgets(linha, 255, fin);
	for(unsigned i=0; i<strlen(linha)-1; i++){
          if(linha[i]=='"') aspas=!aspas;
	  if(aspas||linha[i]!=' '){if(linha[i]!='"') str+=linha[i];}
	  else{if(str!="") args.push_back(str);str="";}
	}   
	if(str.length()>0) args.push_back(str);
	str="";
	add_command(args);
	args.clear();	
      }
      fclose(fin);      
    }
    else{
      std::cerr<<"The file is not open!"<<std::endl;
    }  
  }
  
  
  void Lz5_Interpreter::clear(lz5_Result_Struct r){
    r.object="";
    r.method="";
    r._int.clear();
    r._unsignedShort.clear();
    r._unsignedLong.clear();
    r._unsigned.clear();
    r._float.clear();
    r._double.clear();
    r._string.clear();
    r._char.clear();
    r.__int.clear();
    r.__float.clear();
    r.__double.clear();
    r.__string.clear();
    r.__char.clear();
    r.__unsignedShort.clear();
    r.__unsignedLong.clear();
    r.__unsigned.clear();
  }

}
