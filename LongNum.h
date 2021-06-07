/*

Long number operation

including + - * / % 


*/
#ifndef _GUOJTIM_LONGNUM
#define _GUOJTIM_LONGNUM 1

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class LongNum{
	public:
		bool minus = false;
		vector<int> v;
		LongNum(){
			vector<int> v(1,0);
		}
		LongNum(const LongNum & n){
			minus = n.minus;
			v = vector<int>(n.v);
		}
		LongNum(int num){
			if(num == 0) v.push_back(0);
			if(num < 0){
				minus = true;
				num = num * -1;
			}
			for(;num;num/=10)v.push_back(num%10);
			if(v[0] == 0 && v.size() == 1) minus = false;
		} 
		LongNum(string s){
			for(int i = s.length()-1 ; i >= 0 ; i--) {
				if (s[i] == '-') minus = true;
				else v.push_back(s[i]-'0');
			}
			if(v[0] == 0 && v.size() == 1) minus = false;
		}
		LongNum(vector<int> s){
			v = vector<int>(s);
			for(int i = v.size()-1;i>=0;i--){
				if(v[i] == 0) v.pop_back();
				else break;
			}
			if(v.size() == 0){
				v.push_back(0);
			}
			if(v[0] == 0 && v.size() == 1) minus = false;
		}
		Print(){
			if(minus) cout << "-";
			for(int i = v.size()-1 ; i >= 0 ; i--){
				cout << v[i];
			}
			cout << endl;
		}
		bool operator> (const LongNum & L){
			if (minus && !L.minus)return false;
			else if (!minus && L.minus) return true;
			else{
				if(v.size() > L.v.size()){//length of *this > length of L
					return true ^ minus;
					// xor(result,minus) 
					// -1000 < -1  =>  len(*this) > len(L) but minus = 1
				}else if(v.size() < L.v.size()){
					return false ^ minus;
				}else{
					//len(*this) == len(L)
					//compare each digit
					int c = v.size()-1;
					for(;c >= 0;c--){
						if(v[c] > L.v[c]) return true ^ minus;
						else if(v[c] < L.v[c]) return false ^ minus;
					} 
					if(c == -1) return false; // *this == L
				}
			}
		}
		bool operator> (long long int n){
			return operator>(LongNum(n));
		}
		bool operator< (const LongNum & L){
			if (minus && !L.minus)return true;
			else if (!minus && L.minus) return false;
			else{
				if(v.size() > L.v.size()){//length of *this > length of L
					return false ^ minus;
					// xor(result,minus) 
					// -1000 < -1  =>  len(*this) > len(L) but minus = 1
				}else if(v.size() < L.v.size()){
					return true ^ minus;
				}else{
					//len(*this) == len(L)
					//compare each digit
					int c = v.size()-1;
					for(;c >= 0;c--){
						if(v[c] > L.v[c]) return false ^ minus;
						else if(v[c] < L.v[c]) return true ^ minus;
					} 
					if(c == -1) return false; // *this == L
				}
			}
		}
		bool operator< (long long int n){
			return operator<(LongNum(n));
		}
		bool operator== (const LongNum & L){
			if(v.size() != L.v.size() || minus != L.minus) return false;
			int c = v.size()-1;
			for(;c>=0;c--){
				if(v[c] != L.v[c]) return false;
			}
			return true;
		}
		bool operator== (long long int n){
			return operator==(LongNum(n));
		}
		bool operator>= (const LongNum & L){
			return !operator<(L);
		}
		bool operator>= (long long int n){
			return !operator<(LongNum(n));
		}
		bool operator<= (const LongNum & L){
			return !operator>(L);
		}
		bool operator<= (long long int n){
			return !operator>(LongNum(n));
		}
		LongNum operator+(const LongNum & L ){
			if (!(minus ^ L.minus)) {
				LongNum out = LongNum(addition(v,L.v));
				out.minus = minus;
				return out;
			}else{
				LongNum left = *this,right = L;
				left.minus = false;right.minus = false;
				if (left == right){
					return LongNum(0);
				}
				if (left > right && minus){
					// -x + y => -(x-y)
					LongNum out = LongNum(subtraction(v,L.v));
					out.minus = true;
					return out;
				}else if (left > right && L.minus){
					// x + (-y) => (x-y)
					return LongNum(subtraction(v,L.v));
				}else if(left < right && minus){
					// -x + y => (y-x)
					return LongNum(subtraction(L.v,v));
				}else{
					LongNum out = LongNum(subtraction(L.v,v));
					out.minus = true;
					return out;
				}
			}
		}
		LongNum operator+(long long int n){
			return operator+(LongNum(n));
		} 
		LongNum operator-(const LongNum & L ){
			LongNum right = L;
			right.minus = !right.minus; 
			return operator+(right);
		} 
		LongNum operator-(long long int n){
			return operator+(n*-1);
		} 
		LongNum operator-(){
			LongNum t = *this;
			t.minus = !t.minus;
			return t;
		} 
		
		LongNum operator*(long long int n){
			return operator*(LongNum(n));
		}
		
		LongNum operator*(const LongNum & L ){
			vector<int> newn(v.size()+L.v.size(),0);
			for(int i = 0 ; i < v.size();i++){
				for(int j = 0 ; j < L.v.size();j++){
					newn[i+j]+=v[i]*L.v[j];
				}
			}
			int c = 0;
			for(int i = 0 ; i < newn.size();i++){
				newn[i]+=c;
				c = newn[i] / 10;
				newn[i] %= 10;
			}
			LongNum out = LongNum(newn);
			out.minus = minus ^ L.minus;
			return out;
		}
		
		LongNum operator/ (const LongNum & L){
			LongNum out = LongNum(divide(v,L.v).first);
			if(!(out.v[0] == 0 && out.v.size() == 1)) out.minus = minus^L.minus;
			return out;
		}
		LongNum operator/(long long int n){
			return operator/(LongNum(n));
		}
		LongNum operator% (const LongNum & L){
			return LongNum(divide(v,L.v).second);
		}
		LongNum operator% (long long int n){
			return LongNum(divide(v,LongNum(n).v).second);
		}
		
		vector<int> addzero(const vector<int> source,int num){
			vector<int> n(num,0);
			for(int i = 0 ; i < source.size();i++){
				n.push_back(source[i]);
			}
			return n;
		}
		
		pair<vector<int>,vector<int> > divide(vector<int> dividend,vector<int> divisor){
			pair<vector<int>,vector<int> > result;
			int zeros = (dividend.size() - divisor.size());
			zeros = (zeros > 0 ? zeros : 0);
			vector<int> out(zeros+1,0);
			for(int cnt = 0;zeros >= 0;zeros--,cnt++){
				vector<int> newdivisor = addzero(divisor,zeros);
				while(LongNum(dividend) >= LongNum(newdivisor)){
					LongNum db = LongNum(dividend);
					out[cnt]+= 1;
					dividend = subtraction(dividend,newdivisor);
				}
			}
			reverse(out.begin(),out.end());
			result.first = out;
			result.second = dividend;
			return result;
		}
		
		vector<int> addition(const vector<int> & augend,const vector<int> & addend){
			int c = 0;
			vector<int> newn;//new number
			int i;
			for(i = 0 ; i < min(augend.size(),addend.size());i++){
				if(augend[i]+addend[i]+c > 9){
					newn.push_back(augend[i]+addend[i]+c-10);c = 1;
				}else{
					newn.push_back(augend[i]+addend[i]+c);c = 0;
				}
			}
			for(;i < max(augend.size(),addend.size());i++){
				if(augend.size() > addend.size() && augend[i]+c > 9) {
					newn.push_back(augend[i]+c-10);c = 1;
				} else if(augend.size() < addend.size() && addend[i]+c > 9){
					newn.push_back(addend[i]+c-10);c = 1;
				}else if(augend.size() > addend.size()){
					newn.push_back(augend[i]+c);c = 0;
				}else {
					newn.push_back(addend[i]+c);c = 0;
				}
			}
			if (c) newn.push_back(1);
			return newn;
		}
		vector<int> subtraction(const vector<int> & minuend,const vector<int> & subtrahend){
			// minuend - subtrahend
			// to note , minuend > subtrahend
			//
			int i = 0;
			int c = 0;
			bool iszero = true;
			vector<int> newn;//new number
			for(; i < subtrahend.size();i++){
				if (minuend[i] < subtrahend[i]+c){
					iszero = (10-c-subtrahend[i]+minuend[i] == 0 && iszero);
					newn.push_back(10-c-subtrahend[i]+minuend[i]);
					c=1;
				}else{
					iszero = (minuend[i]-subtrahend[i]-c == 0 && iszero);
					newn.push_back(minuend[i]-subtrahend[i]-c);
					c = 0;
				}
			}
			for(; i<minuend.size();i++){
				newn.push_back(minuend[i]-c);
				c = 0;
			}
			return newn;
		}
		
		operator bool(){
			return !(v.size() == 1 && v[0] == 0);
		}
		
		LongNum operator%=(const LongNum & L){
			LongNum o = operator%(L);
			v = vector<int>(o.v);
			return o;
		}
		
		LongNum operator*=(const LongNum & L){
			LongNum o = operator*(L);
			v = vector<int>(o.v);
			return o;
		}
		
		LongNum operator/=(const LongNum & L){
			LongNum o = operator/(L);
			v = vector<int>(o.v);
			return o;
		}
		
		
		
};
#endif
