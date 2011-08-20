//****************************************************************************************************
//* Lz5_Commands_db.cpp                                                                              *
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

#include"Lz5_Commands_db.h"
#include<fstream>
#include"lz5.h"

using std::string;
using std::vector;
using std::find;

namespace lz5
{  
  void Lz5_Commands_db::add(vector<string>& a){
    unsigned int i = 2;
    object.push_back(a[0]);
    command.push_back(a[1]);            
    vector<string> par;  
    while(i<a.size()){
      if(a[i]!=""){par.push_back(a[i]);}
      i++;
    }
    parameters.push_back(par);    
  }
  
  
  short Lz5_Commands_db::seek(string c){    
    if(c=="help"){help();return -1;}
    for(unsigned short i=0;i<command.size(); i++){
      if(command[i]==c){return i;}
    }
    std:: cout << std::endl<< "Undefined command: "<<'"'<< c << '"'<< "." << " Try " << '"' << "help" << '"' << "." << std::endl;      
    return -1;    
  }  

  void  Lz5_Commands_db::help(){
    for(unsigned c=0;c<command.size(); c++){
      std::cout<<command[c]<<"(";
      for(unsigned p=0;p<parameters[c].size(); p++){
	std::cout<<green<<parameters[c][p]<<normal;
	if(p<parameters[c].size()-1)std::cout<<", ";
      }
      std::cout<<")"<<std::endl;
    }
  }
}
