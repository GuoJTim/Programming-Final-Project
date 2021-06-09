#include "InverseMatrix.h"
#include "Elimination.h"
#include <iostream>
using namespace std;

int main(){
	Matrix m = Matrix(3,3);
	
	m.setValue(0,0,10);	m.setValue(0,1,5); m.setValue(0,2,-7);
	m.setValue(1,0,-5);	m.setValue(1,1,1); m.setValue(1,2,4);
	m.setValue(2,0,3);	m.setValue(2,1,2); m.setValue(2,2,-2);
	
	
	InverseMatrix IM = InverseMatrix(m);
	Elimination state = Elimination(IM);	
	state.GaussJordanElimination();
	Result r = ((InverseMatrix)state.m).getInverse();
	
	if(r.isInverse){
		r.m.formatted();
	}
	
	
}
