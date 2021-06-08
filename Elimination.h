#ifndef _GUOJTIM_ELIMINATION
#define _GUOJTIM_ELIMINATION 1

#include "LaTeX.h"

#include "Matrix.h"
#include <iostream>
#include <math.h>
using namespace std;

enum Stype{START,SWAP,MULTI,ADDTO};
class Solution{
	public:
		enum Stype prevType;
		Matrix matrix;
		Num t1=0,t2=0,t3=0;
		LaTeX *LTX;
		Solution(Matrix m,LaTeX *LTX=NULL,Stype type=START,Num t1 = 0,Num t2 = 0,Num t3 = 0):matrix(m),
		prevType(type),t1(t1),t2(t2),t3(t3){
			
			if(type == SWAP) cout << "swap " << t1.getValue() << " <-> " << t2.getValue() << endl;
			if(type == MULTI) cout << "multi " << t1.getValue() << " value: " << t2.getValue() << endl;
			if(type == ADDTO) cout << "add " << t1.getValue() << " to " << t2.getValue() << " by value " << t3.getValue() << endl; 
			if(LTX != NULL)
			{
				if(type == SWAP) LTX->addText("\\xrightarrow{\\text{swap " + t1.getValue() + " <-> " + t2.getValue() + "}} ");
				if(type == MULTI) LTX->addText("\\xrightarrow{\\text{multi " +t1.getValue()+" value: " + t2.getValue() + "}} ");
				if(type == ADDTO) LTX->addText("\\xrightarrow{\\text{add " + t1.getValue() + " to " + t2.getValue() + " by value " +t3.getValue() + "}} ");
			}
			m.formatted();
		}
};
class Elimination{
	public:
		vector<Solution> sols;
		Matrix m;
		
		LaTeX *LTX;
		
		Elimination(Matrix m,LaTeX *LTX=NULL):m(m),LTX(LTX){
			sols.push_back(Solution(m,LTX));
		}
		GaussElimination(){
			int j = 0;
			for(int i = 0 ; i < m.R;i++){
				while(j < m.C){
					if(m.getValue(i,j).isZero()) {
						for(int k = i+1 ; k < m.R;k++){
							if(!m.getValue(k,j).isZero()) {
								m.swap(j,k);
								sols.push_back(Solution(m,LTX,SWAP,j,k));
								break;
							}
						}
					}
					if(m.getValue(i,j).isZero()){
						j++;
						continue;
					}else if(!m.getValue(i,j).isOne()){
						Num dis = m.getValue(i,j);
						dis = dis.reciprocal();
						m.multiply(i,dis);
						sols.push_back(Solution(m,LTX,MULTI,i,dis));
					}
					for(int k = i+1; k < m.R;k++){
						//if (k >= m.R || i >= m.C) continue;
						if(m.getValue(k,j).isZero()) continue;
						Num dis = m.getValue(k,j)*Num(-1);
						m.addto(i,k,dis);
						sols.push_back(Solution(m,LTX,ADDTO,i,k,dis));
					}
					break;
				}
			}
		}
		GaussJordanElimination(){
			GaussElimination();
			cout << endl;
			for(int i = m.R -1 ; i >= 0 ; i--){
				for(int j = 0 ; j < m.C;j++){
					if(m.getValue(i,j).isZero()) continue;
					else if(m.getValue(i,j).isOne()){
						//do back-stitution
						for(int k = i-1;k >= 0 ; k--){
							Num dis = m.getValue(k,j)*Num(-1);
							m.addto(i,k,dis);
							sols.push_back(Solution(m,LTX,ADDTO,i,k,dis));
						}
					}
					break;
				}
			}
		}
};
#endif
