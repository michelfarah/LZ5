#ifndef _LZ5_INTERPRETER_H_
#define _LZ5_INTERPRETER_H_

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cctype>
#include "prompt.h"
#include "Lz5_Commands_db.h"

namespace lz5
{
    
  struct lz5_Result_Struct{
    string object;                                  // nome do objeto
    string method;                                  // metodo ou funćão membro
    vector<int> _int;                               // <int>
    vector<unsigned short> _unsignedShort;          // <unsigned short>
    vector<unsigned long> _unsignedLong;            // <unsigned long>
    vector<unsigned> _unsigned;                     // <unsigned>
    vector<float> _float;                           // <float>
    vector<double> _double;                         // <double>
    vector<string> _string;                         // <string>
    vector<char> _char;                             // <char>
    vector<bool> _bool;                             // <bool>
    vector<vector<int> > __int;                     // <int...>
    vector<vector<float> > __float;                 // <float...>
    vector<vector<double> > __double;               // <double...>
    vector<vector<string> > __string;               // <string...>
    vector<vector<char> > __char;                   // <char...>
    vector<vector<unsigned short> > __unsignedShort;// <unsigned short...>
    vector<vector<unsigned long> > __unsignedLong;  // <unsigned long...>
    vector<vector<unsigned> > __unsigned;           // <unsigned...>
    vector<vector<bool> > __bool;                   // <bool...>

    inline lz5_Result_Struct():object(""),method(""),_int(),_unsignedShort(),_unsignedLong(),_unsigned(),_float(),_double(),_string(),_char(),_bool(),__int(),__float(),__double(),__string(),__char(),__unsignedShort(),__unsignedLong(),__unsigned(),__bool(){};

  };
  
  
   
  class Lz5_Interpreter
  { 
  private:    
    Lz5_Commands_db command;
    
  public:
    inline Lz5_Interpreter():command(){};
    lz5_Result_Struct verify(string c);
    void cut(string param, lz5_Result_Struct& R, string &c);
    inline Lz5_Commands_db commands(){return command;}
    inline void add_command(vector<string>& a){command.add(a);}   
    inline size_t command_size(){return command.size();}
    void readcomm(const char* f);
    void clear(lz5_Result_Struct r);
  };
  
  
}

#endif
