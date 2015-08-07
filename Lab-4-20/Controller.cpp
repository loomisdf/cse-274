#include "ListGraph.h"
#include "MatrixGraph.h"

#include <iostream>

using namespace std;

int main() {

	ListGraph lGraph(6);
	lGraph.addEdge(0, 2);
	lGraph.addEdge(0, 3);
	lGraph.addEdge(0, 5);
	lGraph.addEdge(2, 5);
	lGraph.addEdge(5, 3);
	lGraph.addEdge(3, 1);
	lGraph.addEdge(3, 4);

	//cout << lGraph.isEdge(0, 2) << endl;
	//cout << lGraph.isEdge(0, 3) << endl;
	//cout << lGraph.isEdge(2, 4) << endl;

	//cout << lGraph.degree(0) << endl;

	MatrixGraph mGraph(6);
	mGraph.addEdge(0, 2);
	mGraph.addEdge(0, 3);
	mGraph.addEdge(0, 5);
	mGraph.addEdge(2, 5);
	mGraph.addEdge(5, 3);
	mGraph.addEdge(3, 1);
	mGraph.addEdge(3, 4);

	EList list = mGraph.getAdj(3);
	EList::const_iterator it;
	for(it = list.begin(); it != list.end(); it++) {
		cout << *it;
	}
	cout << endl;
	cout << mGraph.size() << endl;

	return 0;
}