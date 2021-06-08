#ifndef _GUOJTIM_LATEXGENERATOR
#define _GUOJTIM_LATEXGENERATOR 1

#include <iostream>
#include <fstream>
using namespace std;
#include "Matrix.h"

class LateX{
	ofstream f;
	Latex(string outFile){
		f.open(outFile);
	}
	~Latex(){
		f.close();
	}
};


#endif
