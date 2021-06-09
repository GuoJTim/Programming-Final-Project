#include "Elimination.h"
#include <iostream>
using namespace std;

int main(){
	Matrix m = Matrix(3,2);
	
	m.setValue(0,0,1);	m.setValue(0,1,1);
	m.setValue(1,0,4);	m.setValue(1,1,7);
	m.setValue(2,0,6);	m.setValue(2,1,5);
	
	
	//Elimination state1 = Elimination(m);
	//state1.GaussElimination();

	
	Elimination state2 = Elimination(m);
	state2.GaussJordanElimination();
	
	
}
