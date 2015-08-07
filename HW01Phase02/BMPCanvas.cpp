/*****
 * Author	: loomisdf
 * Date		: 2015-03-02
 * Sources	: Implementation of BMPCanvas.h, created by: brinkmwj, karroje, and inclezd
 * Purpose	: This file is an implementation of the BMPCanvas class.
*****/

#include "BMPCanvas.h"
#include "Fractal.h"

#include <fstream>

using namespace std;

BMPCanvas::BMPCanvas(string iFileName, int iWidth, int iHeight) {
	setFileName(iFileName);
	setDims(iWidth, iHeight);
}

BMPCanvas::BMPCanvas(string iFileName) {
	setFileName(iFileName);
	read();
}

BMPCanvas::BMPCanvas() {
	setDims(0, 0);
	image = NULL;
	setFileName("");
}

BMPCanvas::~BMPCanvas() {
	//delete[] image; 
	//image = NULL;
}

void BMPCanvas::read() {
	//Open a file
	ifstream file(getFileName() + ".bmp", ios::in | ios::binary);

	int w = 0; //declare variables for width and height
	int h = 0;
	
	readHeader(file, w, h); //This will correctly modify w and h so they are the correct size
	setDims(w, h); // This will set the new image dimensions and re-allocate the memory

	//Read in all of the color information and set the corresponing pixel
	for(int x = 0; x < getWidth(); x++) {
		for(int y = 0; y < getHeight(); y++) {
			Color c = Color(0, 0, 0);
			file.read((char*)&c.blue, 1);
			file.read((char*)&c.green, 1);
			file.read((char*)&c.red, 1);
			setPixel(x, y, c);
		}
	}
}

void BMPCanvas::writeBMP() {
	//Create a new file and name it fileName.bmp
	ofstream file(getFileName() + ".bmp", ios::out | ios::binary);
	//Write the header for the bmp file
	writeHeader(file, getWidth(), getHeight());

	//Write all the color codes found in image
	for(int x = 0; x < getWidth(); x++) {
		for(int y = 0; y < getHeight(); y++) {
			Color c = image[y*getWidth()+x];
			file.write((char*)&c.blue, 1);
			file.write((char*)&c.green, 1);
			file.write((char*)&c.red, 1);
		}
	}
	//close the file
	file.close();
}

void BMPCanvas::setDims(int iWidth, int iHeight) {
	width = iWidth;
	height = iHeight;
	image = new Color[iWidth*iHeight];
}

int BMPCanvas::getWidth() {
	return width;
}

int BMPCanvas::getHeight() {
	return height;
}

void BMPCanvas::setPixel(int x, int y, Color c) {
	//Check to make sure x and y are within the image boundaries
	if(x >= 0 && x <= getWidth()) {
		if(y >= 0 && y <= getHeight()) {
			image[y*getWidth()+x] = c;
		}
	}
	//Else do nothing
}

Color BMPCanvas::getPixel(int x, int y) {
	//Check to make sure x and y are within the image boundaries
	if(x >= 0 && x <= getWidth()) {
		if(y >= 0 && y <= getHeight()) {
			return image[y*getWidth()+x];
		}
	}
	//Else return black 
	return Color(0, 0, 0);
}

void BMPCanvas::blank(bool white) {
	//If white is true, make Color as white, else make it black.
	Color blank = (white) ? Color(255,255, 255) : Color(0, 0, 0);

	for(int x = 0; x < getWidth(); x++) {
		for(int y = 0; y < getHeight(); y++) {
			image[y*getWidth()+x] = blank;
		}
	}
}

string BMPCanvas::getFileName() {
	return fileName;
}

void BMPCanvas::setFileName(string iFileName) {
	fileName = iFileName;
}

