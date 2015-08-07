#include "Bicycle.h"

#include <iostream>

using namespace std;

int main(){
	Bicycle b;
	cout << "start: " << b.getSpeed() << endl;

	cout << "speedUp(5)\n";
	b.speedUp(5);

	cout << "getSpeed: " << b.getSpeed() << endl;

	cout << "applyBrake(15)\n";
	b.applyBrake(15);

	cout << "finish: " << b.getSpeed() << endl;


	return 0;
}