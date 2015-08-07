#include "BST.h"

#include <time.h>

using namespace std;

const int num_students = 100000;

int main(){
	BST<int, int> database;
	int ssn = 100000000;
	int uniqueId = 0;

	const clock_t begin_time = clock();
	for (int i = 0; i < num_students; i++) {
		ssn += rand() % 999999999;
		uniqueId = rand() % (num_students + 1);

		database.insert(uniqueId, ssn);
	}
	cout << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds" << endl;
	cout << "last entry entered:" << database.find(uniqueId) << endl;

	return 0;
}
