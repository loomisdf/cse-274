#include "HashTableLP.h"

using namespace std;

const int size = 20;

HashTableLP::HashTableLP(){
	table = new Entry[size];
	int a = rand() % 10 + 1;
	int b = rand() % 10 + 1;
	m = size;
	n = 0;
}

HashTableLP::HashTableLP(int iM, int iA, int iB) {
	table = new Entry[size];
	m = iM;
	a = iA;
	b = iB;
	n = 0;
}

void HashTableLP::insert(int k, string s) {
	// linear probing
	int index = hash(k) % m;
	while(index <= m){
		if(loadFactor() >= 0.5){
			resize();
		}
		if(table[index].value == "") {
			table[index].value = s;
			n++;
			break;
		} else {
			if(index == m)
				index = 0; // wrap around
			else
				index++;
		}
	}
}

string HashTableLP::find(int k) {

}

void HashTableLP::remove(int k) {

}

int HashTableLP::hash(int k) {
	return a*k + b;
}

void HashTableLP::resize() {

}

double HashTableLP::loadFactor() {
	return ((double)n) / ((double)m);
}
