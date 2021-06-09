#include "LinearEquation.h"
#include <iostream>
using namespace std;

int main(){
	LinearEquation system = LinearEquation();
	system.addEquation("a+d+e=4");
	system.Solve();
}
