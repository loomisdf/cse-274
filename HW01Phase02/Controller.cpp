#include "Fractal.h"
#include "BMPCanvas.h"

#include <fstream>
#include <iostream>

using namespace std;

void testGettersAndSetters(BMPCanvas canvas){
	cout << "---Testing getters and setters---" << endl;

	cout << "Filename: " << canvas.getFileName() << endl;
	cout << "getWidth: " << canvas.getWidth() << endl;
	cout << "getHeight: " << canvas.getHeight() << endl;

	cout << "---end test---" << endl << endl;
}

void testBlank(BMPCanvas canvas) {
	cout << "---Testing Blank Method---" << endl;

	cout << "making things white..." << endl;
	canvas.blank(true); //True means white
	Color c = canvas.getPixel(0, 0);
	cout << c.blue << endl;
	
	cout << "making things black..." << endl;
	canvas.blank(false); //false means black
	c = canvas.getPixel(0, 0);
	cout << c.blue << endl;

	cout << "---end test---" << endl;
}

void testFileReading(string fileName) {
	cout << "---File Read Test---" << endl;

	BMPCanvas canvas = BMPCanvas(fileName);
	cout << "reading file..." << endl;
	canvas.read();
	cout << "changing name..." << endl;
	canvas.setFileName("testFileReading");
	cout << "saveing new file..." << endl;
	canvas.writeBMP();

	cout << "---end test---" << endl;
}

int main(){

    //YOUR CODE STARTS HERE

	MakeSquare256();
	MakeSphere256();

    //YOUR CODE ENDS HERE

    return 0;
}


