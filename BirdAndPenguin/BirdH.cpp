#include "BirdHierarchy.h"

#include <iostream>

using namespace std;

Bird::Bird() {
	name = "";
}

Bird::Bird(string sName) {
	name = sName;
}

bool Bird::canFly() {
	return true;
}

void Bird::printInfo() {
	cout << "Name: " << name << endl;
}

Penguin::Penguin(string sName, int iAge) : Bird(sName){
	age = iAge;
}

void Penguin::printInfo(){
	Bird::printInfo();
	cout << "Age: " << age << endl;
}

bool Penguin::canFly() {
	return false;
}