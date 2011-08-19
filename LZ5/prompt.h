/********************************************************************************************
 * prompt.h
 *
 * Copyright (c) 2008 LuCCA-Z (Laboratório de Computação Científica Aplicada à Zootecnia),
 * Rodovia Comandante João Ribeiro de Barros (SP 294), km 651. UNESP,
 * Dracena, São Paulo, Brazil, 17900-000
 *
 * This file is part of LZ5.
 *
 * LZ5 is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * LZ5 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 * the GNU General Public License for more details. You should have received a copy of the
 * GNU General Public License along with LZ5. If not, see <http://www.gnu.org/licenses/>.
 *
 * Acknowledgements
 *
 * To Dr. Rohan L. Fernando from Iowa State University and Dr. Ricardo Frederico Euclydes
 * from Vicosa Federal University, who had great influence in ideas behind the LZ5's development.
 *
 *******************************************************************************************/

#ifndef _PROMPT_H_
#define _PROMPT_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "algorithm"

#define KEY_TAB       9
#define KEY_ESCAPE    27
#define KEY_INSERT    50
#define KEY_DELETE    51
#define KEY_PAGE_UP   53
#define KEY_PAGE_DOWN 54
#define KEY_UP        65
#define KEY_DOWN      66
#define KEY_RIGHT     67 
#define KEY_LEFT      68
#define KEY_HOME      72
#define KEY_END       70
#define KEY_CONTROL_1 79
#define KEY_CONTROL_2 91
#define KEY_BACKSPACE 127

using std::string;
using std::vector;

namespace lz5
{
  class Prompt
  {
  private:   
    short int arrow;    
    short int column;
    bool insert;
    vector<string> commands;
    vector<string> historic;
    unsigned int it;
    void saveCaret ();
    void loadCaret ();
    void clearLine ();
    bool savehistoric();
    bool loadhistoric();
    void caretLeft (unsigned short int columns);
    void caretRight (long unsigned int columns);
    string findcommands(string value);
    bool loadcommands();
  public:
    Prompt();
    int getch();
    string get(string pchar);
    int get_i(string pchar);
    float get_f(string pchar);
    inline void addcommands(string a) {commands.push_back(a);}
    void add_historic(string v_historic);
  };
  
}

#endif
