#ifndef _GUOJTIM_NUM
#define _GUOJTIM_NUM 1

#include <string> 
#include <algorithm>
#include <math.h>
#include <sstream>

#include "LongNum.h"


using namespace std;

class Num{
	private:
		string itos(LongNum n){
			string s;
			while(n){
				s.push_back( (n % 10).v[0] +'0');
				n/=10;
			}
			reverse(s.begin(),s.end());
			return s;
		}
	public:
		LongNum TOP,BOT;
		bool minus;
		Num(){
		}
		Num(const Num &n){
			TOP = n.TOP;
			BOT = n.BOT;
			reduction();
		}
		Num(string a,string b="1"){
			this->TOP = a;
			this->BOT = b;
			reduction();
		}
		Num(LongNum a , LongNum b = 1){
			TOP = LongNum(a);
			BOT = LongNum(b);
			reduction();
		};
		Num(int a ,int b=1){
			TOP = LongNum(a);
			BOT = LongNum(b);
			reduction();
		};
		Num(double num){
			if(num < 0){
				this->minus = true;
				num *= -1;
			}
			else this->minus = false;
			ostringstream ss;
			ss << num;
			string s(ss.str());
			long long int l = 0;
			for(int i = 0 ; i < s.length();i++){
				if(s[i] == '.') {
					l = s.length() - i - 1;
					break;
				}
			}
			num *= (long long int)pow(10,l);
			this->TOP = (long long int)num;
			this->BOT = (long long int)pow(10,l);
			reduction();
		};
		Num operator+(const Num& b){
			LongNum topa = this->TOP;LongNum topb = b.TOP;
			LongNum bota = this->BOT;LongNum botb = b.BOT;
			LongNum _lcm = this->LCM(botb,bota);
			
			topa *= _lcm/bota;
			topb *= _lcm/botb;
			LongNum _top,_bot;
			
			_top = topa + topb;
			_bot = _lcm;
			Num out = Num(_top,_bot);
			
			out.reduction();
			return out;
		}
		
		Num operator-(const Num& b){
			LongNum topa = this->TOP;LongNum topb = b.TOP;
			LongNum bota = this->BOT;LongNum botb = b.BOT;
			LongNum _lcm = this->LCM(botb,bota);
			topa *= _lcm/bota;
			topb *= _lcm/botb;
			LongNum _top,_bot;
			_top = topa - topb;
			_bot = _lcm;
			
			Num out = Num(_top,_bot);
			out.reduction();
			return out;
		}
		
		Num operator*(const Num& b){
			LongNum topa = this->TOP;LongNum topb = b.TOP;
			LongNum bota = this->BOT;LongNum botb = b.BOT;
			
			if(topa == 0 || topb == 0) return Num(0);
			LongNum _top = topa*topb;
			LongNum _bot = bota*botb;
			LongNum _gcd = this->GCD(_top,_bot);
			_gcd.minus = false;
			
			
			Num num = Num(_top/_gcd,_bot/_gcd);
			num.reduction();
			return num;
		}
		Num operator/(const Num& b){
			LongNum topa = this->TOP;LongNum topb = b.TOP;
			LongNum bota = this->BOT;LongNum botb = b.BOT;
			LongNum _top = topa*botb;
			LongNum _bot = bota*topb;
			LongNum _gcd = this->GCD(_top,_bot);
			
			Num num = Num(_top/_gcd,_bot/_gcd);
			num.reduction();
			return num;
		}
		
		void reduction(){
			if (BOT.minus) TOP.minus = !TOP.minus;
			BOT.minus = false;
			minus = TOP.minus;
			if (TOP == 0) {
				TOP = 0;
				BOT = 1;
			}
			else{
				LongNum _gcd = GCD(this->TOP,this->BOT);
				TOP = TOP/_gcd;
				BOT = BOT/_gcd;
			}
		}
		
		Num reciprocal(){
			Num out = Num(BOT,TOP);
			return out;
		}	
		LongNum GCD(LongNum a,LongNum b){
			a.minus = false;b.minus = false;
			if(b) while((a%=b) && (b%=a));
			return a+b;
		}
		LongNum LCM(LongNum a,LongNum b){
			a.minus = false;b.minus = false;
			return (a*b)/GCD(a,b);
		}
		
		bool operator> (const Num & b){
			LongNum topa = this->TOP;LongNum topb = b.TOP;
			LongNum bota = this->BOT;LongNum botb = b.BOT;
			LongNum _lcm = this->LCM(botb,bota);
			
			topa *= _lcm/bota;
			topb *= _lcm/botb;
			return topa > topb;
		}
		bool operator> (int n){
			return operator>(Num(n));
		}
		bool operator< (const Num & b){
			LongNum topa = this->TOP;LongNum topb = b.TOP;
			LongNum bota = this->BOT;LongNum botb = b.BOT;
			LongNum _lcm = this->LCM(botb,bota);
			
			topa *= _lcm/bota;
			topb *= _lcm/botb;
			return topa < topb;
		}
		bool operator< (int n){
			return operator<(Num(n));
		}
		bool operator== (const Num & b){
			LongNum topa = this->TOP;LongNum topb = b.TOP;
			LongNum bota = this->BOT;LongNum botb = b.BOT;
			LongNum _lcm = this->LCM(botb,bota);
			
			topa *= _lcm/bota;
			topb *= _lcm/botb;
			return topa == topb;
		}
		bool operator== (int n){
			return operator==(Num(n));
		}
		bool operator!= (const Num & b){
			return !operator==(b);
		}
		bool operator!= (int n){
			return !operator==(n);
		}
		
		
		string getLaTeX(){
			if(this->TOP == 0) return "0";
			if(this->BOT == 1) return  (this->minus? "-":"")+ itos(this->TOP);
			return (this->minus? "-":"") + string("{ ")+itos(this->TOP) + string("\\over ")+ itos(this->BOT)+ string("}");
		}
		
		string getValue(){
			if(this->TOP == 0) return "0";
			if(this->BOT == 1) return (this->minus? "-":"")+ itos(this->TOP);
			if(this->BOT == 0) return "ERROR";
			
			string s("/");
			return (this->minus? "-":"")+ itos(this->TOP) + s + itos(this->BOT);
		}
		bool isZero(){
			return TOP == 0;
		}
		
		bool isOne(){
			return TOP == BOT;
		}
};
#endif
