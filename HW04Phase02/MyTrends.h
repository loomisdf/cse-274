/*****
* Author   : loomisdf
* Date     : 2015-31-03
* Sources  : Based on Trends.h written by brinkmwj
* Purpose  : This is a subclass of Trends.h. It contains all the same functions,
*			 plus some more custom ones. It also contains the Entry class.
*/

#include "Trends.h"

class Entry {
public:
	Entry() {
		key = "";
		value = 0;
	}

	Entry(string k, int v) {
		key = k;
		value = v;
	}

	string key;
	int value;
};

class MyTrends : public Trends {
public:
	MyTrends(); // Default Constructor
	~MyTrends(); // Destructor

	void increaseCount(string s, int amount);
	int getCount(string s);
	string getNthPopular(int n);
	int numEntries();

private:
	// Functions for the hashtable
	// The key is a string in this case and amount is used as the value.
	void insert(string key, int amount);
	void reSize(); // Double the size

	int find(string key);
	int hash(int key); // Hash function
	int string2Key(string key); //Turns a string into an integer key
	int hash2(int key);
	double loadFactor();
	

	//Used in the hash table functions
	int a;
	int b;
	int table_size_; //m
	int num_elements_; //n

	Entry* hash_table_; //Where the hashtable is stored.
};