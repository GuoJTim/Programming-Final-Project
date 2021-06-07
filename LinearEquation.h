#ifndef _GUOJTIM_LINEAREQUATION
#define _GUOJTIM_LINEAREQUATION 1

#include "Elimination.h"
#include "Num.h"
#include "Matrix.h"
#include <set>
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
		}
}; 


#endif
