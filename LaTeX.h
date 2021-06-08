#ifndef _GUOJTIM_LATEXGENERATOR
#define _GUOJTIM_LATEXGENERATOR 1

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class LaTeX{
	public:
		string filename;
		LaTeX(string filename):filename(filename){
			ofstream reset(filename);
			reset << "";
			reset.close();
		}
		
		void addText(string s){
			ofstream add(filename,std::ios::app);
			add << s;
			add.close();
		}
		
		~LaTeX(){
		}
};


#endif
