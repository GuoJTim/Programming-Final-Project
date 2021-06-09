#include "Num.h"
#include <iostream>
using namespace std;

int main(){
	Num num1 = Num(123,7);
	cout << num1.getValue() << endl;
	
	Num num2 = Num(4750,6);
	cout << num2.getValue() << endl;
	
	Num num3 = num2.reciprocal();
	cout << num3.getValue() << endl;
	
	Num num4 = num2 * 6;
	cout << num4.getValue() << endl;
	
	Num num5 = num4 - Num(7,4);
	cout << num5.getValue() << endl;
}
