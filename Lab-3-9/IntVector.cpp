#include "IntVector.h";

#include <iostream>

using namespace std;

IntVector::IntVector() {
	this->size = 0;
	this->capacity = MIN_CAPACITY;
	vector = new int[capacity];
}

IntVector::~IntVector() {
	delete vector;
}

void IntVector::push_back(int v) {
	if(size == capacity) {
		resize();
	}
	vector[size] = v;
	size++;
}

void IntVector::pop_back() { 
	if(!isEmpty()) {
		vector[size] = -1;
		size--;
	}
}

void IntVector::resize() {
	if(this->capacity == this->size) {

		// Double the list
		int* newVector = new int[capacity*2];
		for(int i = 0; i < size; i++) {
			newVector[i] = vector[i];
		}
		vector = newVector;
		capacity *= 2;
	} 
	else {

		// Shrink the list
		int* newVector = new int[size];
		for(int i = 0; i < size; i++) {
			newVector[i] = vector[i];
		}
		vector = newVector;
		capacity = size;
	}
}

void IntVector::print_vector() {
	for(int i = 0; i < size; i++) {
		cout << vector[i] << " ";
	}
}

int IntVector::at_index(int k) {
	return vector[k];
}

int IntVector::getSize() {
	return this->size;
}

int IntVector::getCapacity() {
	return this->capacity;
}

bool IntVector::isEmpty() {
	return (this->size == 0) ? true : false;
}

bool IntVector::clear() {
	for(int i = 0; i < size; i++) {
		vector[i] = -1;
	}
	resize();
	size = 0;
	return true;
}

