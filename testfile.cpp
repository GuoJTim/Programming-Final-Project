#include "LinearEquation.h"
#include "Elimination.h"
#include "Matrix.h"
#include "InverseMatrix.h"
#include <iostream>
using namespace std;



int main(){
	int col,row;
	cout << "Row :"; cin >> row; 
	cout << "Col :"; cin >> col; 
	Matrix m = Matrix(row,col);
	for(int i = 0 ; i < row;i++){
		for(int j = 0; j < col;j++){
			string s;
			cin >> s;
			m.setValue(i,j,Num(s));
		}
	}
	
	InverseMatrix AI = InverseMatrix(m);
	Elimination state = Elimination(AI);	
	state.GaussJordanElimination();
	Result r = ((InverseMatrix)state.m).getInverse();
	if(r.isInverse) {
		r.m.formatted();
	}else{
		cout << "this matrix dont have inverse matrix" << endl;
	}
	
	LinearEquation system = LinearEquation();
	system.addEquation("a+b+c+d=0");
	system.addEquation("c-d=6");
	system.Solve();

}
