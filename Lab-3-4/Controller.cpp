#include "IntList.h"

#include <iostream>

using namespace std;

int main() {

	cout << "main is working" << endl;
	IntList* test = new IntList();
	IntListNode* node1 = new IntListNode();
	IntListNode* node2 = new IntListNode();
	IntListNode* node3 = new IntListNode();

	node1->data = 1;
	node2->data = 2;
	node3->data = 3;

	test->getSentinel()->next = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = test->getSentinel();

	test->printList();

	return 0;
}