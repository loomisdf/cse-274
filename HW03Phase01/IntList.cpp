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
	prev = this;
}

//The default constructor for IntList
IntList::IntList() {

	// Create the dummy node
	IntListNode* dummy = new IntListNode();

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

	// Create the new node in memory
	IntListNode* node = new IntListNode();

	// Set the data = i
	node->data = i;

	//The node will point to itself
	node->next = node;
	node->prev = node;

	// Call splice to insert the new node
	// Target item is the sentinel, and the source end and start is only one node. 
	splice(node, node, getSentinel()->prev);
}

void IntList::pop_back() {

	// Check if the list is empty
	if(!isEmpty()) {

		// Node to remove is the sentinels predecessor
		IntListNode* rNode = getSentinel()->prev;

		// Check if rNode is the last in the list
		if(rNode->prev == getSentinel()) {

			// Sentinel will become the only node
			getSentinel()->next = getSentinel();
			getSentinel()->prev = getSentinel();
		} 
		else {

			// The predecessor to rNode will point to the sentinel node
			rNode->prev->next = getSentinel();

			// Set the predecessor to sentinel as the new end
			getSentinel()->prev = rNode->prev;
		}
		
		//Delete the removed node
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
	return (getSentinel()->next == getSentinel()) ? true: false;
}

IntListNode* IntList::head() {
	return (isEmpty()) ? NULL : IntList::sentinel->next;
}

IntListNode* IntList::tail() {
	return (isEmpty()) ? NULL : IntList::sentinel->prev;
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

	// Cut out source start and end
	IntListNode* iStart = sourceStart->prev;
	IntListNode* iEnd = sourceEnd->next;

	// Set the new start and end pointing to each other
	iStart->next = iEnd;
	iEnd->prev = iStart;

	// Create iTarget. iStart and iEnd will be placed in between target and iTarget
	IntListNode* iTarget = target->next;

	sourceEnd->next = iTarget;
	sourceStart->prev = target;

	target->next = sourceStart;
	iTarget->prev = sourceEnd;
}

