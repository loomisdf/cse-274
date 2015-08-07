#include <string>

using namespace std;

class Entry {
public:
	Entry() {
		key = -1;
		value = "";
	}

	Entry(int k, string v) {
		key = k;
		value = v;
	}

	int key;
	string value;
};

class HashTableLP {
public:
	/** Set m, a, and b to some initial values.
	  * Allocate memory for table.
	  * Mark all entries in the table as empty.
	  */
	HashTableLP();

	/** Set m to value iM, a to iA, and b to iB.
	  * Allocate memory for table.
	  * Mark all entries in the table as empty.
	  */
	HashTableLP(int iM, int iA, int iB);

	/** Deallocate the memory used by table
	  */
	~HashTableLP();

	void insert(int k, string s);
	string find(int k);
	void remove(int k);

	// Add other functions as needed

private:
	/** Calculates the hash function for input k as a*k+b
	  */
	int hash(int k);
	void resize();
	double loadFactor();

	Entry* table;
	int m;
	int a, b;
	// add other data members if needed
	int n; // Number of entries
};