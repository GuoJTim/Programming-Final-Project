#include "LinearEquation.h"
#include "Elimination.h"
#include "Matrix.h"
#include "InverseMatrix.h"
#include "LaTeX.h"
#include <iostream>

using namespace std;




int main(){
	int col,row;
	LaTeX out = LaTeX("testfile.txt");
	cout << "Row :"; cin >> row; 
	cout << "Col :"; cin >> col; 
	Matrix m = Matrix(row,col,&out);
	for(int i = 0 ; i < row;i++){
		for(int j = 0; j < col;j++){
			string s;
			cin >> s;
			m.setValue(i,j,Num(s));
		}
	}
	Elimination state = Elimination(m,&out);	
	state.GaussJordanElimination();

}
