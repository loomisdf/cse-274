
#include <string>
#include "IntStringList.h"

using namespace std;

#define MAX_CHAIN_LENGTH = 3; 

class HashTableSC {
public:
	HashTableSC();
	void insert(int key, string value);
	void remove(int key);
	void rehash(int key);
	void resize(); 
	string find(int key);

	int key;
	string value;

private:
	int m; //prime number
	int a, b;
	int c; //constant
	IntStringList* hashTable; //This should be changed to a list that stores strings
};