/********************************************************************************************
 * prompt.cpp
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

#include "prompt.h"


namespace lz5
{
  
  Prompt::Prompt(): arrow(-1), column(), insert(false), commands(), historic(), it(0){
    loadcommands();
    loadhistoric();
  }

  string Prompt::get(string pchar)
  {
    using std::cout;
    using std::cin;
    using std::endl;
    int value = 0;    
    string prompt_var;
    unsigned char a;
    arrow = -1; 
    column = 0;
    insert = false;
    it=0;
    //__fpurge(stdin); //limpa o buffer de teclado
    cout << endl << pchar;    
    do
      {
	if (value!=0)	  
	  cout << (unsigned char) value;
	value=getch();
	if(value==KEY_TAB) //Tecla Tab
	  {
	    int i, cont=0;
	    string nova;
	    if((prompt_var.size()!=0) && (column==(short int)prompt_var.size()))
	      {
		do
		  {
		    for (i=(int)prompt_var.size()-1;i>=0;i--)
		      {
			if (((prompt_var.substr(i,1)==" ") || (prompt_var.substr(i,1)=="=")) && (i!=(int)prompt_var.size()-1))
			  break;
		      }
		    nova=findcommands(prompt_var.substr(i+1,prompt_var.size()));
		    if (nova.size()!=0)
		      {
			if (cont==0)
			  cont=(int)prompt_var.size()-i-1;
			for (int v=cont;v>=1;v--)
			  {
			    cout << '\b';
			    cout << ' ';
			    cout << '\b';
			  }
			cont=(int)nova.size();
			cout << nova;
		      }
		    value=getch();
		  }while(value==9); //Continua se a Tecla for Tab
		if (nova.size()!=0)	
		  {
		    prompt_var= prompt_var.erase(i+1,prompt_var.size())+nova;
		    column=(short int)prompt_var.size();
		  }		
	      }
	    else
	      value=0;
	  }
	if (value==KEY_ESCAPE) //Código do ESC
	  {	  
	    value=getch();
	    if (value==KEY_CONTROL_1)
	      {
		value=getch();
		if (value==KEY_END)  //Tecla End
		  {
		    if (column!=(short int)prompt_var.size())
		      caretRight(prompt_var.size()-column);
		    column=(short int)prompt_var.size();
		    value=0;
		  }
		else if (value==KEY_HOME) //Tecla Home
		  {
		    for (int v=column;v>=1;v--)
		      caretLeft(1);
		    column=0;
		    value=0;
		  }
		value=0;
	      }
	    else if (value==KEY_CONTROL_2)  //Controle de Teclas
	      {
		value=getch();
		if (value==KEY_INSERT) //Tecla Insert
		  {
		    insert=(insert?false:true);
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_DELETE) //Tecla Delete
		  {
		    if (column!=(short int)prompt_var.size())
		      {
			for (int v=column;v>=1;v--)
			  {
			    cout << '\b';			    
			  }									   		   
			prompt_var=prompt_var.erase(column,1);	  
			cout << prompt_var+" ";
			for (short int v=(short int)prompt_var.size();v>column-1;v--)
			  {
			    cout << '\b';
			  }
		      }
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_PAGE_UP) //Tecla PageUP
		  {
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_PAGE_DOWN) //Tecla PageDown
		  {
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_UP) //Tecla UP
		  {	  
		    string nova;
		    if(historic.size()>0)
		      {			    
			if (arrow<=0)
			  arrow=(short int)historic.size();
			arrow=(short int)(arrow-1);
			nova = historic[arrow];
			if (nova.size()!=0)
			  {
			    //for (int v=column;v>=1;v--)
			    if (column!=(short int)prompt_var.size())
			      caretRight(prompt_var.size()-column);
			    for (int v=(int)prompt_var.size();v>=1;v--)
			      {
				cout << '\b';
				cout << ' ';
				cout << '\b';
			      }			   		   
			    prompt_var=prompt_var.erase(0,prompt_var.size())+nova;	  
			    cout << prompt_var;
			    column=(short int)prompt_var.size();
			  }			  			    
		      }
		    value=0;
		  }
		else if (value==KEY_DOWN) //Tecla DOWN	
		  {	  
		    string nova;
		    if((historic.size()>0) && (arrow>=0) && (arrow!=(short int)historic.size()-1))
		      {			    
			arrow=(short int)(arrow+1);
			nova = historic[arrow];
			if (nova.size()!=0)
			  {	
			    if (column!=(short int)prompt_var.size())
			      caretRight(prompt_var.size()-column);			
			    for (int v=(int)prompt_var.size();v>=1;v--)				
			      {
				cout << '\b';
				cout << ' ';
				cout << '\b';
			      }			   		   
			    prompt_var=prompt_var.erase(0,prompt_var.size())+nova;	  
			    cout << prompt_var;
			    column=(short int)prompt_var.size();
			  }			  			    
		      }
		    value=0;
		  }		      
		else if (value==KEY_RIGHT) //Tecla Right
		  {
		    if (column<(short int)prompt_var.size())
		      {
			caretRight(1);//cout << "RIGHT";
			column++;
		      }
		    value=0;
		  }
		else if (value==KEY_LEFT) //Tecla Left
		  {
		    if ((column>0) && (prompt_var.size()!=0))
		      {			    			
			caretLeft(1); //cout << "LEFT";    
			column--;
		      }
		    value=0;
		  }
	      }
	    else 
	      {
		if (prompt_var.size()>0) //cout << "ESC";
		  {
		    for (int v=(int)prompt_var.size();v>=1;v--)
		      {
			cout << '\b';
			cout << ' ';
			cout << '\b';
		      }			   		   
		    prompt_var=prompt_var.erase(0,prompt_var.size());		    
		    column=1;
		  }		    
		value=0;
	      }	      	  
	    rewind(stdin);
	  }
	if(value==63) //Tecla ?
	  {	    
	    prompt_var+="list";
	    cout << "list";
	    value=0;
	    column=(short int)prompt_var.size();
	  }
	if(value==KEY_BACKSPACE) //Tecla BackSpace
	  {
	    if (prompt_var.size()!=0)
	      {
		prompt_var=prompt_var.erase(prompt_var.size()-1,1);
		cout << '\b';
		cout << ' ';
		cout << '\b';
		column--;
		if (column<0)
		  column=0;
	      }
	    value=0;
	  }
	if(value!=0)  //Qualquer tecla digitada
	  {	    
	    a=(char)value; //acho que aqui vai dar pau
	    if ((column!=(short int)prompt_var.size()) && (value!=10))
	      {
		if (insert)
		  {
		    prompt_var=prompt_var+" ";
		    for (int v=(int)prompt_var.size()-1;v>=column;v--)
		      prompt_var[v]=prompt_var[v-1];
		  }
		for (int v=column;v>=1;v--)
		  {
		    cout << '\b';			    
		  } 
		prompt_var[column]=a; 		   
		cout << prompt_var;
		for (int v=(int)prompt_var.size();v>column;v--)
		  {
		    cout << '\b';
		  }		
	      }
	    else
	      prompt_var+=a;
	    column++;
	  }
      }while(value!=10);        
    historic.push_back(prompt_var.substr(0,prompt_var.size()-1));
    savehistoric();
    cout << endl;
    return prompt_var.substr(0,prompt_var.size()-1);    
  }

  void Prompt::add_historic(string v_historic)
  {
    historic.push_back(v_historic);
  }

  int Prompt::get_i(string pchar) //retorna valor do tipo inteiro
  {
    using std::cout;
    using std::cin;
    using std::endl;
    int value = 0;    
    string prompt_var;
    unsigned char a;
    arrow = -1; 
    column = 0;
    insert = false;
    it=0;
    //__fpurge(stdin); //limpa o buffer de teclado
    cout << pchar;    
    do
      {
	if (value!=0)	  
	  cout << (unsigned char) value;
	value=getch();
	if(value==KEY_TAB) //Tecla Tab
	  {
	    value=getch();
	    value=0;
	  }
	if (value==KEY_ESCAPE) //Código do ESC
	  {	  
	    value=getch();
	    if (value==KEY_CONTROL_1)
	      {
		value=getch();
		if (value==KEY_END)  //Tecla End
		  {
		    if (column!=(short int)prompt_var.size())
		      caretRight(prompt_var.size()-column);
		    column=(short int)prompt_var.size();
		    value=0;
		  }
		else if (value==KEY_HOME) //Tecla Home
		  {
		    for (int v=column;v>=1;v--)
		      caretLeft(1);
		    column=0;
		    value=0;
		  }
		value=0;
	      }
	    else if (value==KEY_CONTROL_2)  //Controle de Teclas
	      {
		value=getch();
		if (value==KEY_INSERT) //Tecla Insert
		  {
		    insert=(insert?false:true);
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_DELETE) //Tecla Delete
		  {
		    if (column!=(short int)prompt_var.size())
		      {
			for (int v=column;v>=1;v--)
			  {
			    cout << '\b';			    
			  }									   		   
			prompt_var=prompt_var.erase(column,1);	  
			cout << prompt_var+" ";
			for (int v=(int)prompt_var.size();v>column-1;v--)
			  {
			    cout << '\b';
			  }
		      }
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_PAGE_UP) //Tecla PageUP
		  {
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_PAGE_DOWN) //Tecla PageDown
		  {
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_UP) //Tecla UP
		  {	  
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_DOWN) //Tecla DOWN	
		  {	  
		    value=getch();
		    value=0;
		  }		      
		else if (value==KEY_RIGHT) //Tecla Right
		  {
		    if (column<(short int)prompt_var.size())
		      {
			caretRight(1);//cout << "RIGHT";
			column++;
		      }
		    value=0;
		  }
		else if (value==KEY_LEFT) //Tecla Left
		  {
		    if ((column>0) && (prompt_var.size()!=0))
		      {			    			
			caretLeft(1); //cout << "LEFT";    
			column--;
		      }
		    value=0;
		  }
	      }
	    else 
	      {
		if (prompt_var.size()>0) //cout << "ESC";
		  {
		    for (int v=(int)prompt_var.size();v>=1;v--)
		      {
			cout << '\b';
			cout << ' ';
			cout << '\b';
		      }			   		   
		    prompt_var=prompt_var.erase(0,prompt_var.size());		    
		    column=1;
		  }		    
		value=0;
	      }	      	  
	    rewind(stdin);
	  }
	if(value==63) //Tecla ?
	  {	    
	    prompt_var+="list";
	    cout << "list";
	    value=0;
	    column=(short int)prompt_var.size();
	  }
	if(value==KEY_BACKSPACE) //Tecla BackSpace
	  {
	    if (prompt_var.size()!=0)
	      {
		prompt_var=prompt_var.erase(prompt_var.size()-1,1);
		cout << '\b';
		cout << ' ';
		cout << '\b';
		column--;
		if (column<0)
		  column=0;
	      }
	    value=0;
	  }
	if(value!=0)  //Qualquer tecla digitada
	  {
	    string ca="0123456789";
	    a=(char)value;
	    int i=(int)ca.find(a,0);
	    const char BEEP = '\a';
	    if (((i>=0) && (i<=11))) 
	      {
		if ((column!=(short int)prompt_var.size()) && (value!=10))
		  {
		    if (insert)
		      {
			prompt_var=prompt_var+" ";
			for (int v=(int)prompt_var.size()-1;v>=column;v--)
			  prompt_var[v]=prompt_var[v-1];
		      }
		    for (int v=column;v>=1;v--)
		      {
			cout << '\b';			    
		      } 
		    prompt_var[column]=a; 		   
		    cout << prompt_var;
		    for (int v=(int)prompt_var.size();v>column;v--)
		      {
			cout << '\b';
		      }		
		  }
		else
		  prompt_var+=a;
		column++;
	      }
	    else if (value!=10)
	      {
		cout << BEEP;	
		value=0;
	      }
	  }
      }while(value!=10);            
    cout << endl;
    prompt_var=prompt_var.substr(0,prompt_var.size());    
    int valor=atoi(prompt_var.c_str());    
    return valor;
  }
  
  float Prompt::get_f(string pchar) //retorna valor do tipo float
  {
    using std::cout;
    using std::cin;
    using std::endl;
    int value = 0;    
    string prompt_var;
    unsigned char a;
    arrow = -1; 
    column = 0;
    insert = false;
    it=0;
    //__fpurge(stdin); //limpa o buffer de teclado
    cout << pchar;    
    do
      {
	if (value!=0)	  
	  cout << (unsigned char) value;
	value=getch();
	if(value==KEY_TAB) //Tecla Tab
	  {
	    value=getch();
	    value=0;
	  }
	if (value==KEY_ESCAPE) //Código do ESC
	  {	  
	    value=getch();
	    if (value==KEY_CONTROL_1)
	      {
		value=getch();
		if (value==KEY_END)  //Tecla End
		  {
		    if (column!=(short int)prompt_var.size())
		      caretRight(prompt_var.size()-column);
		    column=(short int)prompt_var.size();
		    value=0;
		  }
		else if (value==KEY_HOME) //Tecla Home
		  {
		    for (int v=column;v>=1;v--)
		      caretLeft(1);
		    column=0;
		    value=0;
		  }
		value=0;
	      }
	    else if (value==KEY_CONTROL_2)  //Controle de Teclas
	      {
		value=getch();
		if (value==KEY_INSERT) //Tecla Insert
		  {
		    insert=(insert?false:true);
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_DELETE) //Tecla Delete
		  {
		    if (column!=(short int)prompt_var.size())
		      {
			for (int v=column;v>=1;v--)
			  {
			    cout << '\b';			    
			  }									   		   
			prompt_var=prompt_var.erase(column,1);	  
			cout << prompt_var+" ";
			for (int v=(int)prompt_var.size();v>column-1;v--)
			  {
			    cout << '\b';
			  }
		      }
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_PAGE_UP) //Tecla PageUP
		  {
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_PAGE_DOWN) //Tecla PageDown
		  {
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_UP) //Tecla UP
		  {	  
		    value=getch();
		    value=0;
		  }
		else if (value==KEY_DOWN) //Tecla DOWN	
		  {	  
		    value=getch();
		    value=0;
		  }		      
		else if (value==KEY_RIGHT) //Tecla Right
		  {
		    if (column<(short int)prompt_var.size())
		      {
			caretRight(1);//cout << "RIGHT";
			column++;
		      }
		    value=0;
		  }
		else if (value==KEY_LEFT) //Tecla Left
		  {
		    if ((column>0) && (prompt_var.size()!=0))
		      {			    			
			caretLeft(1); //cout << "LEFT";    
			column--;
		      }
		    value=0;
		  }
	      }
	    else 
	      {
		if (prompt_var.size()>0) //cout << "ESC";
		  {
		    for (int v=(int)prompt_var.size();v>=1;v--)
		      {
			cout << '\b';
			cout << ' ';
			cout << '\b';
		      }			   		   
		    prompt_var=prompt_var.erase(0,prompt_var.size());		    
		    column=1;
		  }		    
		value=0;
	      }	      	  
	    rewind(stdin);
	  }
	if(value==63) //Tecla ?
	  {	    
	    prompt_var+="list";
	    cout << "list";
	    value=0;
	    column=(short int)prompt_var.size();
	  }
	if(value==KEY_BACKSPACE) //Tecla BackSpace
	  {
	    if (prompt_var.size()!=0)
	      {
		prompt_var=prompt_var.erase(prompt_var.size()-1,1);
		cout << '\b';
		cout << ' ';
		cout << '\b';
		column--;
		if (column<0)
		  column=0;
	      }
	    value=0;
	  }
	if(value!=0)  //Qualquer tecla digitada
	  {
	    string ca="0123456789.,";
	    a=(char)value;
	    int i=(int)ca.find(a,0);
	    const char BEEP = '\a';
	    if (((i>=0) && (i<=11))) 
	      {
		if (a==',')
		  {
		    a='.';
		    value=a;
		  }
		if ((a=='.') && !(prompt_var.find(a,0)>prompt_var.size()))
		  {
		    value=0;
		    a=(char)value;
		  }
		if ((column!=(short int)prompt_var.size()) && (value!=10))
		  {
		    if (insert)
		      {
			prompt_var=prompt_var+" ";
			for (int v=(int)prompt_var.size()-1;v>=column;v--)
			  prompt_var[v]=prompt_var[v-1];
		      }
		    for (int v=column;v>=1;v--)
		      {
			cout << '\b';			    
		      } 
		    prompt_var[column]=a; 		   
		    cout << prompt_var;
		    for (int v=(int)prompt_var.size();v>column;v--)
		      {
			cout << '\b';
		      }		
		  }
		else
		  prompt_var+=a;
		column++;
	      }
	    else if (value!=10)
	      {
		cout << BEEP;	
		value=0;
	      }
	  }
      }while(value!=10);            
    cout << endl;
    prompt_var=prompt_var.substr(0,prompt_var.size());    
    float valor=(float)atof(prompt_var.c_str());    
    return valor;
  }


  int Prompt::getch( )
  {
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
  }
  
  void Prompt::saveCaret ()
  {
    std::cerr << "\033[s";
  }
  
  void Prompt::loadCaret ()
  {
    std::cerr << "\033[u";
  }
  
  void Prompt::clearLine ()
  {
    std::cerr << "\033[2K>";
  }
  
  void Prompt::caretLeft (unsigned short int columns)
  {
    std::cerr << "\033[" << columns << 'D';
  }
  
  void Prompt::caretRight (long unsigned int columns)
  {
    std::cerr << "\033[" << columns << 'C';
  }
  

  string Prompt::findcommands(string value)
  {  
    using std::string;
    int f = 0;    
    string var;
    if (commands.size() == 0)
      {
	return "";
      }
    else
      {
	while( f<(short int)commands.size() ) 
	  {
	    var=commands[it];
	    if (var.substr(0,value.size())==value)
	      {
		it++;
		if (it>=commands.size())
		  it=0;
		return var;
	      }
	    it++;
	    if (it>=commands.size())
	      it=0;
	    f++;
	  }
      }
    return "";
  }
  
  bool Prompt::loadcommands()
  {
    using std::sort;  
    using std::ifstream;
    string line, c, command;	
    bool space;
    ifstream myfile ("commands.lz5");
    if (myfile.is_open())
      {
	while (! myfile.eof() )
	  {
	    getline(myfile,line);
	    if (line.size()!=0){
	      space=false;
	      command="";
	      for(unsigned i=0; i<line.size(); i++){
		if(line[i]==' '){
		  if(space) break;
		  space=true;		  
		}
		if((space)&&(line[i]!=' '))command+=line[i];
	      }
	      commands.push_back(command);
	    }
	  }	
	commands.push_back("quit");
	myfile.close();      
      }
    else    
      return false;    
    sort(commands.begin(), commands.end());
    return true;  
  }
  
  
  bool Prompt::savehistoric() 
  {  	
    using std::ofstream;
    using std::endl;
    int init=0;
    ofstream hout;
    string line;
    hout.open("historic.sml");
    if (hout.is_open())
      {
	if (historic.size()>500)
	  init=(int)historic.size()-500;
	for (unsigned f=init;f<historic.size();f++)
	  {
	    line=historic[f];
	    if (line.size()!=0)
	      hout << line << endl;
	  }
	hout.close();
      }
    else
      return false;
    return true;
  }  
  
  bool Prompt::loadhistoric() 
  {
    using std::ifstream;
    string line, c;	
    ifstream myfile ("historic.sml");
    if (myfile.is_open())
      {
	while (! myfile.eof() )
	  {
	    getline(myfile,line);
	    if (line.size()!=0)
	      historic.push_back(line);
	  }	
	myfile.close();      
      }
    else    
      return false;    
    return true;
  }  
}
