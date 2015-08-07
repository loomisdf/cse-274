/***
 * Author	: loomisdf
 * Date		: 2015-2-23
 * Sources	: Tester.h class created by brinkmwj, and modified by inclezd
 * Purpose	: This file is an implementation of the IntList, and IntListNode classes.
 ***/

#include "IntList.h"

#include <iostream>

using namespace std;

//The default constructor for IntListNode
IntListNode::IntListNode() {
	data = -1;
	next = this;
}

//The default constructor for IntList
IntList::IntList() {

	// Create the dummy node
	IntListNode* dummy = new IntListNode();
	dummy->next = dummy;

	// Point Sentinel to the dummy node
	IntList::sentinel = dummy;
}

//The destructor for IntList
IntList::~IntList() {
	clear();
	delete IntList::sentinel;
}

// Pushes a node onto the list. It will be positioned at the front of the list
void IntList::push_back(int i) {

	// Find the last node in the list
	IntListNode* lastNode = new IntListNode();
	while(lastNode->next != sentinel) {
		lastNode = sentinel->next;
	}

	// initialize the new node 
	IntListNode* insertNode = new IntListNode();
	insertNode->data = i;

	// Point the last node in the list to the new node
	lastNode->next = insertNode;

	// Point the new node to the sentinel
	insertNode->next = sentinel;
}

void IntList::pop_back() {

	// Don't remove if sentinel is the only node
	if(sentinel->next != sentinel) {

		// Find the second to last node
		// If only one element the second to last node will be the sentinel
		IntListNode* secondToLastNode = new IntListNode();
		while(secondToLastNode->next->next != sentinel) {
			secondToLastNode = sentinel->next;
		}

		// Remove the last node
		IntListNode* rNode = secondToLastNode->next;
		secondToLastNode->next = sentinel;

		delete rNode;
	}
	
}

void IntList::clear() {

	//While the list is not empty
	while(!isEmpty()) {

		//Pop off the last element in the list
		pop_back();
	}
}

bool IntList::isEmpty() {
	return (sentinel->next == sentinel) ? true: false;
}

IntListNode* IntList::head() {
	return (isEmpty()) ? NULL : IntList::sentinel->next;
}

IntListNode* IntList::tail() {
	if(isEmpty()) {
		return NULL;
	}
	IntListNode* tail = new IntListNode();
	tail = sentinel->next;
	while(tail->next != sentinel) {
		tail = tail->next;
	}
	return tail;
}

IntListNode* IntList::getSentinel() {
	return sentinel;
}

void IntList::printList() {
	IntListNode* pos = new IntListNode();
	IntListNode* sent = getSentinel(); 
	pos = sent->next;
	while(pos != sent) {
		cout << pos->data << " ";
		pos = pos->next;
	}
	cout << endl;
}

void splice(IntListNode* sourceStart, IntListNode* sourceEnd, IntListNode* target) {

	// How do I check for all of the assert statements in this method?
	// assert(a and b belong to the same list)
	// assert(b is not before a)
	// assert(t is not an element of <a,...,b>)

	IntListNode* iEnd = sourceEnd->next;
	IntListNode* iStart = sourceEnd->next;
	while(iStart->next != sourceStart) {
		iStart = iStart->next;
	}

	// Mend the list a and b come from
	iStart->next = iEnd;

	// Create iTarget. iStart and iEnd will be placed in between target and iTarget
	IntListNode* iTarget = target->next;

	sourceEnd->next = iTarget;
	target->next = sourceStart;

	sourceEnd->next = iTarget;
}

