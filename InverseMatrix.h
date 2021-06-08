#ifndef _GUOJTIM_INVERSEMATRIX
#define _GUOJTIM_INVERSEMATRIX 1

#include "LaTeX.h"
#include "Matrix.h"
typedef struct Result{
	Matrix m;
	bool isInverse;
};
class InverseMatrix:public Matrix{
	public:	
		InverseMatrix(Matrix x):Matrix(x){
			if(type != MATRIX) return;
			type = INVERSE;
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
		
		Result getInverse(){
			bool invm = (C == R*2);
			for(int i = 0 ; i < R ; i++){
				invm = colVector[i].v[i].isOne() && invm;
			}
			Matrix m = Matrix(R,R);
			for(int i = 0 ; i < R;i++){
				for(int j = 0 ; j < R;j++){
					m.setValue(i,j,colVector[i].v[j+R]);
				}
			}
			return Result{m,invm};
		}
}; 
#endif
