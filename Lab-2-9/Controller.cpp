#include <iostream>
#include <fstream>

using namespace std;

void exercise1() {
	cout << "---Exercise1---" << endl;
	//Create a variable
	int N;

	//Print message and put input into N
	cout << "Enter an integer: ";
	cin >> N;

	int* arr = new int[N*N];
	for(int x = 0; x < N; x++) {
		for(int y = 0; y < N; y++) {
			arr[y*N+x] = (x + y) % 10;
		}
	}
	
	for(int x = 0; x < N; x++) {
		for(int y = 0; y < N; y++) {
			cout << arr[x*N+y];
		}
		cout << endl;
	}

	delete[] arr;
	arr = NULL;
}

void exercise2() {
	cout << "---Exercise2---" << endl;

	ofstream out("arr.bin", ios::out | ios::binary);

	//Create a variable
	int N;

	//Print message and put input into N
	cout << "Enter an integer: ";
	cin >> N;

	int* arr = new int[N*N];
	for(int x = 0; x < N; x++) {
		for(int y = 0; y < N; y++) {
			arr[y*N+x] = (x + y) % 10;
		}
	}

	out.write((char*)arr,N*N*sizeof(int));
	out.close();
	delete[] arr;
	arr = NULL;
	
	arr = new int[N*N];
	ifstream in("arr.bin", ios::in | ios::binary);
	in.read((char*)arr,N*N*sizeof(int));

	for(int x = 0; x < N; x++) {
		for(int y = 0; y < N; y++) {
			cout << arr[x*N+y];
		}
		cout << endl;
	}
		
	delete[] arr;
	arr = NULL;
}

int main() {
	exercise1();
	exercise2();

	return 0;
}