#ifndef _GUOJTIM_LINEAREQUATION
#define _GUOJTIM_LINEAREQUATION 1

#include "Elimination.h"
#include "Num.h"
#include "Matrix.h"
#include <math.h>
#include <set>
#include <map>
using namespace std;

class Equation{
	public:
		vector<Num> mem = vector<Num>(26,Num(0,1));
		vector<int> variable;
		Num constNum = Num(0,1);
		Equation(string s){
			int index = 0;
			string temp;
			for(index = 0; s[index] != '=' && index < s.length();index++){
				if(s[index] >= 'a' && s[index] <= 'z'){
					variable.push_back(s[index]-'a');
					
					mem[s[index]-'a'] = mem[s[index]-'a'] + Num(temp.empty() ? "1":(temp == "-" ? "-1": temp)  );
					temp.clear();
				}else if(s[index] == '+') continue;
				else{
					temp = temp + s[index];
				}
			}
			temp.clear();
			for(index++;index < s.length();index++){
				temp = temp + s[index];
			}
			constNum = Num(temp);
			cout << s << endl;
		}
		void showDebug(){
			for(int i = 0 ,first = 0; i < 26;i++){
				if(!mem[i].isZero()){
					if(first) cout << (mem[i].minus ? "":"+");
					cout << (mem[i].isOne() ? "":mem[i].getValue()) << char(i+'a');
					first = 1;
				}
			}
			cout << "=" << constNum.getValue() << endl;
		}
};


class LinearEquation{
	public:
		vector<Equation> eq;
		set<int> variable;
		vector<Num> constNum;
		LinearEquation(){}
		addEquation(string s){
			Equation neq = Equation(s);
			for(int i = 0 ; i < neq.variable.size();i++){
				variable.insert(neq.variable[i]);
			}
			eq.push_back(neq);
			constNum.push_back(neq.constNum);
		}
		
		Solve(){
			Matrix m = Matrix(eq.size(),variable.size());
			for(int i = 0 ; i < eq.size();i++){
				int j = 0;
				for(set<int>::iterator it = variable.begin();it != variable.end();it++,j++){
					m.setValue(i,j,eq[i].mem[*it]);
				}
			}
			AugmentMatrix am = AugmentMatrix(m,constNum);
			Elimination em = Elimination(am);
			em.GaussJordanElimination();
			
			if (noSolution(em.m)){
				cout << "these linear equations has no solution" << endl;
			}else if (oneSolution(em.m)){
				cout << "these linear equations has only 1 soluiton:" << endl;
				int j = 0;
				for(set<int>::iterator it = variable.begin();it != variable.end();it++,j++){
					cout << char(*it+'a') << "=" << em.m.getValue(j,am.C-1).getValue() << endl;
				}
			}else{
				cout << "inf solution" << endl;
				int temp = 1;
				map<int,int> var;
				for(int i = em.m.R-1; i >= 0 ; i--){
					
					int leadingone = -1;
					for(int j = 0 ; j < em.m.C-1;j++) {
						if(!em.m.getValue(i,j).isZero()) {
							leadingone = j;
							break;
						}
					}
					
					if(leadingone == -1) continue; //full zero row
					
					for(int j = leadingone+1;j < em.m.C-1;j++){
						if(!em.m.getValue(i,j).isZero() && !var[j]){
							cout << "let " << char((*variable.begin()+j)+'a') << "= (temp" << temp << ") in RealNumber." << endl;
							var[j] = temp++;
						}
					}
					
					cout << char((*variable.begin()+leadingone)+'a') << " = " << em.m.getValue(i,em.m.C-1).getValue();
					for(int k = leadingone+1 ; k < em.m.C-1;k++){
						if(var[k]){
							Num n = em.m.getValue(i,k) * Num(-1);
							if (!n.minus) cout << "+" << n.getValue() << "(temp" << var[k] << ")";
							else cout << n.getValue() << "(temp" << var[k] << ")";
						}
					}
					cout << endl;
				}
			}		
		}
		
		
		bool noSolution(Matrix m){
			bool nosol = false;
			for(int i = 0 ; i < m.R && !nosol;i++){
				bool fullzero = true;
				int j = 0 ;
				for(; j < m.C-1 && !nosol;j++){
					fullzero = m.getValue(i,j).isZero() && fullzero;
				}
				nosol = fullzero && !m.getValue(i,j).isZero(); // fullzero and last not zero
			}
			return nosol;
		}
		bool oneSolution(Matrix m){
			bool onesol = (m.R >= variable.size() );
			for(int i = 0 ; i < min(m.R,(int)variable.size());i++) onesol = onesol && m.getValue(i,i).isOne();
			return onesol;
		}
		
}; 


#endif
