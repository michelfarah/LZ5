//****************************************************************************************************
//* Lz5_Commands_db.h                                                                                *
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

#ifndef __LZ5_COMMANDS_DB_H__
#define __LZ5_COMMANDS_DB_H__

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cctype>

using std::string;
using std::vector;

namespace lz5
{
  
  class Lz5_Commands_db
  {
  private:
    vector<string> object;
    vector<string> command;
    vector<vector<string> > parameters;
  public:
    inline Lz5_Commands_db():object(),command(),parameters(){};
    
    inline string get_object(unsigned i){return object[i];}
    inline string get_command(unsigned i){return command[i];}
    inline size_t get_parameters_size(unsigned int i){return parameters[i].size();}
    inline string get_parameters(unsigned i, unsigned j){return parameters[i][j];}

    inline size_t size(){return object.size();}
    short seek(string c);
    void add(vector<string>& a);
    void clear();
    void help();
  };
  
}

#endif
