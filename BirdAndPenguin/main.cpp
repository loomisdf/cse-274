#include <iostream>

#include "BirdHierarchy.h"

using namespace std;

int main(){
	Bird b ("Barbie");
	Penguin p ("Tweety", 5);

	b.printInfo();
	cout << endl;

	p.printInfo();
	cout << endl;

	cout << "Barbie's ability to fly: " << b.canFly() << endl << endl;
	cout << "Tweety's ability to fly: " << p.canFly() << endl;

	return 0; 

}


