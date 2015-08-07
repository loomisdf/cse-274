
#include "IntList.h";
#include "Tester.h";

#include <iostream>

using namespace std;

void testPrintList() {
	IntList* testIntList_t = new IntList();
	IntListNode* node1 = new IntListNode();
	IntListNode* node2 = new IntListNode();

	node1->data = 1;
	node2->data = 2;

	testIntList_t->getSentinel()->next = node1;
	testIntList_t->getSentinel()->prev = node2;

	node1->prev = testIntList_t->getSentinel();
	node1->next = node2;

	node2->prev = node1;
	node2->next = testIntList_t->getSentinel();

	testIntList_t->printList();
}

int main() {
	cout << "Main is working" << endl;

	Tester test;
	test.doTests();

	testPrintList();

	return 0;
}