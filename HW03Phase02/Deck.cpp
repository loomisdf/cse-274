#include "Deck.h"

#include <iostream>

using namespace std;

//Done
Deck::Deck() {

	// Place the numbers 0-51 into deckList
	for(int i = 0; i < 52; i++) {
		Deck::deckList.push_back(i);
	}
}

//TODO
void Deck::shuffle() {

	// Cut the deck into two decks A and B
	IntList* A = new IntList();
	IntList* B = new IntList();
	cut(A, B);

	// Take turns putting 0, 1, 2 cards from the BOTTOM of A and B, back into deckList
	int numToTake;

	// Stop taking cards when A and B are empty
	while(!(A->isEmpty()) || !(B->isEmpty())) {
		numToTake = rand() % 3; // random number from 0-2

		// Take from A
		for(int i = 0; i < numToTake; i++) {
			if(!A->isEmpty()) {
				//deckList.printList();
				splice(A->head(), A->head(), deckList.getSentinel());
			}
		}
		numToTake = rand() % 3;

		//Take from B
		for(int i = 0; i < numToTake; i++) {
			if(!B->isEmpty()) {
				//deckList.printList();
				splice(B->head(), B->head(), deckList.getSentinel());
				
			}
		}
	}
	delete A;
	delete B;
}

//Done
IntListNode* Deck::getListHead() {
	return Deck::deckList.head();
}

//Done
void Deck::cut(IntList* A, IntList* B) {
	// Get the center node of deckList (position is 25)
	IntListNode* center = Deck::deckList.head();
	for(int i = 0; i < 25; i++) {
		center = center->next;
	}

	// Place cards 0-25 into A
	splice(Deck::deckList.head(), center, A->getSentinel());

	// Place cards 26-51 into B
	splice(Deck::deckList.head(), Deck::deckList.tail(), B->getSentinel());
}
