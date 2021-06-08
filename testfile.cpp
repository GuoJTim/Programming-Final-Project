#include "LinearEquation.h"
#include "Elimination.h"
#include "Matrix.h"
#include "InverseMatrix.h"
#include "LaTeX.h"
#include <iostream>

using namespace std;




int main(){
//	int col,row;
//	LaTeX out = LaTeX("testfile.txt");
//	cout << "Row :"; cin >> row; 
//	cout << "Col :"; cin >> col; 
//	Matrix m = Matrix(row,col,&out);
//	for(int i = 0 ; i < row;i++){
//		for(int j = 0; j < col;j++){
//			string s;
//			cin >> s;
//			m.setValue(i,j,Num(s));
//		}
//	}
//	
//	InverseMatrix AI = InverseMatrix(m);
//	Elimination state = Elimination(AI,&out);	
//	state.GaussJordanElimination();
//	Result r = ((InverseMatrix)state.m).getInverse();
//	if(r.isInverse) {
//		r.m.formatted();
//	}else{
//		cout << "this matrix dont have inverse matrix" << endl;
//	}

	LaTeX out = LaTeX("testfile.txt");
	
	LinearEquation system = LinearEquation(&out);
	system.addEquation("a+b+c+d+e+f+g+h+4i=0");
	system.addEquation("4a+9i=1");
	
	system.Solve();

}
