#include "IntVector.h"

#include <iostream>

using namespace std;

int main() {

	IntVector v(3);
	v.push_back(2);
	v.push_back(10);
	v.print_vector();

	cout << endl;

	v.pop_back();
	v.print_vector();

	cout << endl;

	cout << "at index 0 = " << v.at_index(0) << endl;

	v.push_back(3);
	v.print_vector();

	cout << endl;

	v.push_back(5);
	v.print_vector();

	cout << endl;

	v.push_back(10);
	v.print_vector();

	cout << endl;

	cout << "capacity = " << v.getCapacity() << endl;

	return 0;
}