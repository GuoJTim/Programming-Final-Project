#ifndef _GUOJTIM_MATRIX
#define _GUOJTIM_MATRIX 1

#include "Num.h"
#include "LaTeX.h"
#include <iostream>
#include <iomanip>
using namespace std;

//class LaTeX;



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

enum MatrixType{MATRIX,AUGMENT,INVERSE};
class Matrix{ 
	public:
		enum MatrixType type;
		vector<rowVector> colVector;
		int R,C;
		
		LaTeX *LTX;
		
		
		Matrix(int r,int c,LaTeX *LTX=NULL):LTX(LTX){
			type = MATRIX;
			R=r;C=c;
			for(int i = 0 ; i < r;i++) colVector.push_back(rowVector(c));
		}
		Matrix(const Matrix&m){
			LTX = (m.LTX);
			type = m.type;
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
	
		void write(){
			if(LTX == NULL) return;
			
			LTX->addText("\\begin{bmatrix} ");
			
			for(int i = 0 ; i < R;i++){
				for(int j = 0 ; j < C;j++){
					if(j) LTX->addText(" & ");
					LTX->addText(colVector[i].getValue(j).getLaTeX());
				}
				if(i != R-1) LTX->addText("\\\\ \n");
			}
			
			
			LTX->addText("\\end{bmatrix} \\\\");
			
		}
		
		void formatted(){
			write();
			/*
			/begin{bmatrix}
			
			
			/end{bmatrix}
			*/
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
			if(type != MATRIX) return;
			type=AUGMENT;
			for(int i = 0;i<R;i++){
				colVector[i].v.push_back(constMatrix[i]);
			}
			C++;
		}
};
#endif
