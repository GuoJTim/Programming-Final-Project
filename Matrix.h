#ifndef _GUOJTIM_MATRIX
#define _GUOJTIM_MATRIX 1

#include "Num.h"
#include <iostream>
#include <iomanip>
using namespace std;

class rowVector{
	public:
		vector<Num> v;
		rowVector(int s = 0){
			v = vector<Num>(s,0);
		}
		rowVector(vector<Num> vec){
			v = vector<Num>(vec);
		}
		
		void setValue(int p,Num val){
			v[p] = val;
		}
		Num getValue(int p){
			return v[p];
		}
		
		void swap(rowVector & nv){
			rowVector temp = nv;
			nv = *this;
			*this = temp;
		}
		void multiply(Num value){
			for(int i = 0 ; i < v.size();i++) {
				v[i] = v[i] * value;
			}
		}
		void addto(rowVector & nv,Num value){
			for(int i = 0 ; i <v.size();i++){
				nv.v[i] = nv.v[i] + (v[i] * value);
			}
		}
};

class Matrix{ 
	public:
		vector<rowVector> colVector;
		int R,C;
		Matrix(int r,int c){
			R=r;C=c;
			for(int i = 0 ; i < r;i++) colVector.push_back(rowVector(c));
		}
		Matrix(const Matrix&m){
			R=m.R;C=m.C;
			colVector = m.colVector;
		}
		
		void swap(int i,int j){
			colVector[i].swap(colVector[j]);
		}
		void multiply(int i,Num value){
			colVector[i].multiply(value);
		}
		void addto(int i,int j,Num value=1){
			colVector[i].addto(colVector[j],value);
		}
		
		void setValue(int i,int j,Num value){
			colVector[i].setValue(j,value);
		}
		Num getValue(int i,int j){
			return colVector[i].getValue(j);
		}
		
		
		void formatted(){
			if (R == 1){
				printf("¡e");
				for(int i = 0 ;i < C;i++){
					if(i) cout << " ";
					cout << colVector[0].getValue(i).getValue();	
				}
				printf("¡f");
			}else{
				for(int i = 0 ; i < R;i++){
					if(!i) cout << "¢z";
					else if(i == R-1)cout << "¢|";
					else cout << "¢x";
					for(int j = 0 ; j < C;j++){
						cout << setw(17) << colVector[i].getValue(j).getValue();
					}
					if(!i) cout << "¢{";
					else if(i == R -1) cout << "¢}";
					else cout << "¢x";
					cout << endl;
				}
			}
		}
};

class AugmentMatrix:public Matrix{
	public:
		AugmentMatrix(Matrix x,vector<Num> constMatrix):Matrix(x){
			for(int i = 0;i<R;i++){
				colVector[i].v.push_back(constMatrix[i]);
			}
			C++;
		}
};

class AugmentInverse:public Matrix{
	public:
		AugmentInverse(Matrix x):Matrix(x){
			// to know if want to find a inverse matrix A^-1 , A must be square matrix
			//
			//
			for(int i = 0;i<R;i++){
				for(int j = 0 ; j <C;j++){
					if(i==j) colVector[i].v.push_back(1);
					else colVector[i].v.push_back(0);
				}
			}
			C*=2;
		}
}; 
#endif
