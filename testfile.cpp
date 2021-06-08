#include "LinearEquation.h"
#include "Elimination.h"
#include "Matrix.h"
#include <iostream>
using namespace std;



int main(){
//	int col,row;
//	cout << "Row :"; cin >> row; 
//	cout << "Col :"; cin >> col; 
//	Matrix m = Matrix(row,col);
//	for(int i = 0 ; i < row;i++){
//		for(int j = 0; j < col;j++){
//			string s;
//			cin >> s;
//			m.setValue(i,j,Num(s));
//		}
//	}
//	
//	//AugmentInverse AI = AugmentInverse(m);
//	Elimination state = Elimination(m);	
//	state.GaussJordanElimination();
	LinearEquation system = LinearEquation();
	system.addEquation("a+b+c+d=5");
	system.addEquation("c-d=1");
	system.Solve();

}
