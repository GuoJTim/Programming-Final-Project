#include "LongNum.h"
#include <iostream>
using namespace std;

int main(){
	LongNum num1 = LongNum("777777777777777777777777715648946515648945616");
	num1.Print();
	
	LongNum num2 = LongNum(5);
	LongNum num3 = num1 * num2;
	num3.Print();
	
	LongNum num4 = num1 / 5;
	LongNum num5 = num1 % 5;
	num4.Print();
	num5.Print();
	LongNum num6 = num4 * 5 + num5;
	num6.Print();
} 
