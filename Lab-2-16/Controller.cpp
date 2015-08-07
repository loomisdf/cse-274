#include <iostream>
#include <ctype.h>

using namespace std;

int main() {
	char* s = (char*)malloc(255 * sizeof(char));
	cout << "Input a string: ";
	cin.getline(s, 255);
	int blankSpace = 0;
	for(int i = 0; i < strlen(s); i++) {
		if(s[i] == ' ') {
			blankSpace++;
		}
	}
	cout << "Number of blank spaces = " << blankSpace << endl;

	cout << "Input another string: ";
	cin.getline(s, 255);
	for(int i = 0; i < strlen(s); i++) {
		s[i] = tolower(s[i]);
	}
	cout << "String in lowercase: " << s << endl;

	//Check for palindrome
	cout << "Input another string: ";
	cin.getline(s, 255);
	char* sDest = (char*)malloc(255);
	strncpy(sDest, s, 255);
	int count = 0;
	for(int i = strlen(s)-1; i >= 0; i--) {
		if(sDest[count] != s[i]) {
			cout << "Your string is not a plalindrome, terribly sorry" << endl;
			break;
		}
		count++;
	}
	

	//free(sDest);
	free(s);
	return 0;
}