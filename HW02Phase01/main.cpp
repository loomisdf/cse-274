#include "encrypt.h"
#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

/**
 * Add your own code to the main function below, as specified there.
 */

void test1() {
	RSAint i = chars2RSAint("ABC.", strlen("ABC.")+1);
    cout << "i: (should print 776159809) " << i << endl;
   
    char * s = (char*)malloc(strlen("ABC.")*sizeof(char) + sizeof(char));
    RSAint2chars(i, s, strlen("ABC.")+1);
    cout << "Should print ABC.: " << s << endl;
}

void test2() {
	RSAint i = chars2RSAint("ABCD.", strlen("ABCD.")+1);
    cout << "i: (should print 198713754177) " << i << endl;
   
    char * s = (char*)malloc(strlen("ABCD.")*sizeof(char) + sizeof(char));
    RSAint2chars(i, s, strlen("ABCD.")+1);
    cout << "Should print ABCD.: " << s << endl;
}

void testGenerateKey() {
	cout << "---testGenerateKey---" << endl;
	RSAint p = randomPrime(minPrimeLimit, maxPrimeLimit);
	RSAint q = randomPrime(minPrimeLimit, maxPrimeLimit);
	RSAint e, d, n;
	generateKey(p, q, &e, &d, &n);

	int newSize = 0;
	RSAint* msg = RSAencrypt("Success", sizeof("Success")+1, &newSize, e, n);

	int newnewSize = 0;
	char* newMsg = RSAdecrypt(msg, newSize,  &newnewSize, d, n);
	cout << "New MSG = " << newMsg << endl;
	cout << "---" << endl;
}

void crackTheCode() {
	cout << "---crackTheCode---" << endl;

	ifstream file1("keys.txt");
	RSAint n = 0;
	RSAint e = 0;
	char* nKey = (char*)malloc(9*sizeof(char));
	char* eKey = (char*)malloc(6*sizeof(char));
	nKey[9] = '\0';
	eKey[6] = '\0';

	//Read in n and e
	file1.read(nKey, 9);
	file1.read(eKey, 6);
	sscanf(nKey, "%d", &n);
	sscanf(eKey, "%d", &e);

	cout << "n = " << n << endl;
	cout << "e = " << e << endl; 
	RSAint d = RSACracker(e, n); // Get the secret RSA key
	cout << "cracked value d = " << d << endl;
	file1.close();

	ifstream file2("encrypted.txt");
	char* nextChar = (char*)malloc(1*sizeof(char));
	nextChar[1] = '\0';
	
	//Count the number of characters and space in the file
	int numChars = 0;
	int numSpaces = 0;
	while (!file2.eof()) {
    	file2.read(nextChar, 1);
		if(nextChar[0] == ' ') {
			numSpaces++;
		}
		numChars++;
    }
	file2.close();

	//Create two arrays for storing information
	char* theMessage = (char*)malloc(numSpaces*sizeof(char));
	theMessage[numSpaces] = '\0';
	char* temp = (char*)malloc(20*sizeof(char));
	temp[20] = '\0';
	RSAint num= 0;

	//Open the file once more
	file2.open("encrypted.txt");

	RSAint* allNumbers = (RSAint*)malloc(numSpaces*sizeof(RSAint));
	allNumbers[numSpaces] = '\0';
	int numCounter = 0;
	int counter = 0;
	for(int x = 0; x < numChars; x++) {
    	file2.read(nextChar, 1);
		if(nextChar[0] == ' ') {
			sscanf(temp, "%d", &num);
			allNumbers[numCounter] = num;
			numCounter++;
			counter = 0;
			for(int i = 0; i < 10; i++) {
				temp[i] = ' ';
			}
		} else {
			temp[counter] = nextChar[0];
			counter++;
		}
    }
	int newSize = 0;
	theMessage = RSAdecrypt(allNumbers, numSpaces, &newSize, d, n);
	cout << theMessage << endl;
	file2.close();
	cout << "---" << endl;
}

int main() {
	// for testing and grading - do not change!
	test1();
	test2();

	/**
	 * Write your code below this comment.
	 *	- Read the public key components n and e from the file keys.txt. (n is listed first.)
	 *	- Read the contents of the file encrypted.txt, containing a sequence of RSAints 
	 *		separated by spaces (which was produced by applying the encryption algorithm to a file) 
	 *		using the public key (e,n) you just read in. 
	 *	- Crack the encryption and print out the original message.
	 */
	
	crackTheCode();
	return 0;
}
