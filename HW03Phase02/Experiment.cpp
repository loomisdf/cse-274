/*****
 * Author   : brinkmwj
 * Date     : 2009-07-23
 * Sources  : All code is original
 * Purpose  : I have implemented the chiSquared function for you, do not change it.
 * Note     : N/A
 *****/

#include "Experiment.h"
#include <fstream>
#include <iomanip>
#include "Deck.h"
#include <sstream>
#include <iostream>

#define MAXNUMSHUFFLES 15

using namespace std;

/*
 * DO NOT CHANGE THIS FUNCTION! Add all your code after this!
 */ 
double chiSquared(long* rowHead, int rowLength){
	long rowTotal = 0;
	double expected = 0.0;
	double chiSq = 0.0;
	for(int i=0;i<rowLength; i++){
		rowTotal += rowHead[i];
	}
	expected = ((double)rowTotal)/((double)rowLength);

	for(int i=0; i<rowLength; i++){
		chiSq = chiSq + (((rowHead[i] - expected)*(rowHead[i] - expected))/expected);
	}

	return chiSq;
}

/*
 * Add your doOneExperiment here
 */

double doOneExperiment(int numshuffles) {
	long* countMatrix = new long[52*52];

	//Initialize matrix to 0
	for(int x = 0; x < 52; x++) {
		for(int y = 0; y < 52; y++) {
			countMatrix[x*52 + y] = 0;
		}
	}


	//Create the deck and shuffle it numShuffles times
	IntListNode* node;
	for(int k = 0; k < NUMEXPERIMENTS; k++) {
		Deck deck;
		for(int i = 0; i < numshuffles; i++) {
			deck.shuffle();
		}

		node = deck.getListHead();
		for(int x = 0; x < 52; x++) {
			countMatrix[node->data * 52 + x]++;
			node = node->next;
		}
	}

	stringstream oss;
	oss << "table" << numshuffles << ".txt";
	
	ofstream table(oss.str(), ios::out | ios::binary);
	for(int x = 0; x < 52; x++) {
		for(int y = 0; y < 52; y++) {
			string s = to_string(countMatrix[y*52 + x]);
			char const *pchar = s.c_str();
			table.write(pchar, 1);
		}
		table.write("\n", 1);
	}
	table.close();

	// Calculate chiSquared
	double chiS = chiSquared(countMatrix, 52);

	// If fair
	if(chiS < CRITICALVALUE) {
		cout << numshuffles << " was fair, with chi^2 = " << chiS << endl;
	} 
	// If Biased
	else if(chiS >= CRITICALVALUE) {
		cout << numshuffles << " was biased, with chi^2 = " << chiS << endl;
	}
	
	return chiS;
}

/*
 * Add your doExperimentRun here
 */

void doExperimentRun() {
	int numShuffles = 0;
	while(numShuffles <= MAXNUMSHUFFLES) {
		if(doOneExperiment(numShuffles) < CRITICALVALUE) {
			break;
		}
		numShuffles++;
	}
}