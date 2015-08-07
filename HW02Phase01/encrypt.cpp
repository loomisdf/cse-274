/*****
* Author   : loomisdf
* Date     : 2015-02-19
* Sources  : encrpyt.h, created by karroje and modified by inclezd.
* Purpose  : This file is an implementation of the encrypt.h file.
*****/

/**
*	Keys come in pairs
*	(e,n) - public key
*	(d,n) - private key
**/

#include "encrypt.h"
#include "rsa_functions.h"

#include <string.h>
#include <cassert>
#include <iostream>
#include <bitset>

using namespace std;

RSAint chars2RSAint(char* str, int c) {
	//Preconditions
	assert(str != NULL);
	assert(c >= 0);
	assert(c <= sizeof(RSAint));

	RSAint rsa = 0;

	for(int i = 0; i < c; i++)  {
		rsa = rsa | (RSAint(str[i]) << (8*i)); //add the character to the right most position
	}
	return rsa;
}

void RSAint2chars(RSAint enc, char* str, int c) {
	assert(enc >= 0 && c >= 0 && str != NULL);
    for (int i=0; i < c; i++) {
		*(str + i) = (char) enc % 256;
        enc = enc >> 8;
      }
}

void generateKey(RSAint p, RSAint q, RSAint* e, RSAint* d, RSAint* n) {
	//Preconditions
	assert(e != NULL && d != NULL && n != NULL &&
		p > minPrimeLimit && p < maxPrimeLimit &&
		q > minPrimeLimit && q < maxPrimeLimit && 
		p != q);
	//n = p*q
	*n = p*q;

	//Create Eulers totient function: phi(n)
	RSAint m = *n - (p + q - 1);
	do {
		*e = randomPrime(minPrimeLimit, maxPrimeLimit);
	} while(!isCoPrime(*e, m) || *e < 10000); //If 'e' and phiN are NOT coprime, make 'e' a new random prime. 

	*d = multiplicative_inverse(*e, m); // Make d the multiplicative inverse of e and phiN

	//Postconditions
	assert(*n == p*q);
	assert((*e)*(*d) % ((p-1)*(q-1)) == 1);
	assert(*e > 10000);
}

RSAint* RSAencrypt(char* msg, int size, int* newSize, RSAint e, RSAint n) {
	assert(msg != NULL && newSize != NULL && size > 0);
	//use modular_power, x^a % m
	RSAint* secret_msg = (RSAint*)malloc(size*sizeof(RSAint));

	char* addTo = (char*)malloc(3*sizeof(char));
	addTo[3] = '\0';

	RSAint c = 0; //Modular power result
	RSAint m = 0; //RSAint result
	int addNum; //Keeps track of how many chars are being put through chars2RSAint
	int counter = 0; //Keeps track of where to place RSAints in secret_msg
	
	for(int i = 0; i < size; i +=3){
		if(size - i < 4 && size - i > 2) {
			addTo[0] = msg[i];
			addTo[1] = msg[i+1];
			addNum = 2;
		} else if(size - i < 3) {
			addTo[0] = msg[i];
			addNum = 1;
		} else {
			addTo[0] = msg[i];
			addTo[1] = msg[i+1];
			addTo[2] = msg[i+2];
			addNum = 3;
		}
		m = chars2RSAint(addTo, addNum);
		c = modular_power(m, e, n);
		secret_msg[counter] = c;

		counter++;
	}
	*newSize = counter;
	return secret_msg;
}

char* RSAdecrypt(RSAint* encoding, int size, int* newSize, RSAint d, RSAint n) {
	char* msg = (char*)malloc((size*3)*sizeof(char));

	//Decode all of the RSAints in encoding
	for(int i = 0; i < size; i++) {
		encoding[i] = modular_power(encoding[i], d, n);
	}

	// NextChunk is an array for storing 3 characters at a time.
	char* nextChunk = (char*)malloc(3*sizeof(char));
	int counter = 0; // Keeps track of position in msg
	for(int i = 0; i < size; i++) {
		RSAint2chars(encoding[i], nextChunk, 3); // Convert an RSAint into 3 chars
		for(int x = 0; x < 3; x++) {
			msg[counter] = nextChunk[x];
			counter++;
		}
	}
	*newSize = (size*3);
	return msg;
}

RSAint RSACracker(RSAint e, RSAint n) {
	RSAint p = 0;
	RSAint q = 0;
	RSAint d = 0;
	do{
		p = randInt(minPrimeLimit, maxPrimeLimit);
		q = randInt(minPrimeLimit, maxPrimeLimit);
	} while(n != (p*q));

	RSAint m = n - (p + q - 1); 
	d = multiplicative_inverse(e, m); // Make d the multiplicative inverse of e and phiN

	return d; 
}


