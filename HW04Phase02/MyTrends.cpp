#include "MyTrends.h"

#include <iostream>
#include <array>
const int kInitialSize = 10;

using namespace std;

// Implement the constructor
MyTrends::MyTrends() {
	a = rand() % 11 + 1;
	b = rand() % 21 + 10;
	table_size_ = kInitialSize;
	hash_table_ = new Entry[kInitialSize];
	num_elements_ = 0;
}

MyTrends::~MyTrends() {
	delete hash_table_;
}

void MyTrends::increaseCount(string s, int amount) {
	insert(s, amount);
}

int MyTrends::getCount(string s) {
	return find(s);
}

string MyTrends::getNthPopular(int n) {
	Entry nthPopular("", 0);
	Entry curr("", 0);

	//Previously the most popular
	Entry ignore("",0);
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < table_size_; j++) {
			if (hash_table_[j].key == "") {
				// Ignore the empty value
				continue;
			}
			else {
				curr = hash_table_[j];

				// First time with no ignore value
				if (ignore.value == 0){
					// Nthpopular hasn't been set yet
					if (nthPopular.value == 0){
						nthPopular = curr;
					}
					// current value is greater
					else if (curr.value > nthPopular.value) {
						nthPopular = curr;
					}
					// same amount, tie breaker
					else if (curr.value == nthPopular.value) {
						if (curr.key < nthPopular.key) {
							nthPopular = curr;
						}
					}
				}
				// Ignore has a value
				else {
					if (curr.value < ignore.value) {
						// Nthpopular hasn't been set yet
						if (nthPopular.value == 0){
							nthPopular = curr;
						}
						// current value is greater
						else if (curr.value > nthPopular.value) {
							nthPopular = curr;
						}
						// same amount, tie breaker
						else if (curr.value == nthPopular.value) {
							if (curr.key < nthPopular.key) {
								nthPopular = curr;
							}
						}
					}
					else if (curr.value == ignore.value)  {
						if (curr.key > ignore.key) {
							// Nthpopular hasn't been set yet
							if (nthPopular.value == 0){
								nthPopular = curr;
							}
							// current value is greater
							else if (curr.value > nthPopular.value) {
								nthPopular = curr;
							}
							// same amount, tie breaker
							else if (curr.value == nthPopular.value) {
								if (curr.key < nthPopular.key) {
									nthPopular = curr;
								}
							}
						}
					}
				}
			}
		}
		// Last time through, nth popular has been found
		if (i == n) {
			break;
		}
		ignore = nthPopular;
		nthPopular.key = "";
		nthPopular.value = 0;
	}
	return nthPopular.key;
}

int MyTrends::numEntries() {
	return num_elements_;
}

void MyTrends::insert(string key, int amount) {
	int iKey = string2Key(key);
	if (loadFactor() >= 0.5) {
		reSize();
	}

	int counter = 0;

	while (counter < table_size_){
		int index = (hash(iKey) + counter*hash2(iKey)) % table_size_;
		// If the key has not been seen before
		if (hash_table_[index].key == "") {
			hash_table_[index].key = key;
			hash_table_[index].value += amount;
			num_elements_++;
			break;
		}
		// If they key is already in the table
		else if (hash_table_[index].key == key) {
			hash_table_[index].value += amount;
			break;
		}
		// A collision has occured; loop and find a new place
		counter++;
	}
}

int MyTrends::find(string key) {
	int iKey = string2Key(key);
	int counter = 0;
	while (counter < table_size_){
		int index = (hash(iKey) + counter*hash2(iKey)) % table_size_;

		if (hash_table_[index].key == key) {
			return hash_table_[index].value;
		}
		counter++;
	}

	// Nothing found
	return 0;
}

int MyTrends::hash(int key) {
	return a*key + b;
}

int MyTrends::hash2(int key) {
	return 1 + (hash(key) % (table_size_ - 1));
}

int MyTrends::string2Key(string key) {
	int iKey = 1;
	const int modifier = key.length();
	for (int i = 0; i < key.length(); i++) {
		char c = key.at(i);
		iKey += c * i * modifier;
	}
	return iKey;
}

double MyTrends::loadFactor() {
	return (double)num_elements_ / (double)table_size_;
}

void MyTrends::reSize() {
	table_size_ *= 2;
	Entry* newArr = new Entry[table_size_];
	for (int i = 0; i < table_size_ / 2; i++) {
		newArr[i] = hash_table_[i];
	}

	hash_table_ = new Entry[table_size_];

	// Re insert the old entries with the new table size
	for (int i = 0; i < table_size_ / 2; i++) {
		Entry curr(newArr[i].key, newArr[i].value);
		int iKey = string2Key(newArr[i].key);

		int counter = 0;

		while (counter < table_size_){
			int index = (hash(iKey) + counter*hash2(iKey)) % table_size_;

			// If the key has not been seen before
			if (hash_table_[index].key == "") {
				hash_table_[index].key = curr.key;
				hash_table_[index].value += curr.value;
				break;
			}
			// A collision has occured; loop and find a new place
			counter++;
		}
	}
	
}