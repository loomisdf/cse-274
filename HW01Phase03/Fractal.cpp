/*****
 * Author   : inclezd (modification of code from karroje and brinkmfwj) 
 * Date     : 2013-08-30
 * Purpose  : These functions are utility functions for generating bmp formatted fractals.
 * NOTES    : DO NOT MODIFY ANY OF THE CODE PROVIDED! Write your code below the line at the bottom of this file.
 *****/
#include <iostream>
#include <fstream>

//Windows.h is only needed for readHeader and writeHeader.
#include <Windows.h>
#include "BMPCanvas.h"
#include "Fractal.h"
#include <math.h>
#include <complex>

#pragma comment (lib, "winmm.lib")

using namespace std;

/**
 * Provided functions. DO NOT MODIFY!!!
 **/

// Random Number Generator seed: Seed the random number generator.  Seeds
// from clock if seed_value = 0.
void seedRNG(long seed_value) {
  if (seed_value > 0) 
	  srand(seed_value);
  else {
     double x = timeGetTime();  
     while (x == timeGetTime() );   // BETTER solution: get process ID
    srand(timeGetTime());
  }
}


// Return a random integer in the half-open interval [i,j).
// (Meaning: it returns a number ranging from i up to BUT NOT INCLUDING j.)
int randomNumber(int i, int j) {
	return (int)((j-i)*((1.0*rand()) / (RAND_MAX+1))) + i;
}

//Information on BMP format was provided by www.fileformat.info/format/bmp/egff.htm
void writeHeader(ostream& out, int width, int height){
  if (width % 4 != 0) {
    cerr << "ERROR: There is a windows-imposed requirement on BMP that the width be a multiple of 4.\n";
    cerr << "Your width does not meet this requirement, hence this will fail.  You can fix this\n";
    cerr << "by increasing the width to a multiple of 4." << endl;
    exit(1);
  }

	BITMAPFILEHEADER tWBFH;
	tWBFH.bfType = 0x4d42;
	tWBFH.bfSize = 14 + 40 + (width*height*3);
	tWBFH.bfReserved1 = 0;
	tWBFH.bfReserved2 = 0;
	tWBFH.bfOffBits = 14 + 40;

	BITMAPINFOHEADER tW2BH;
	memset(&tW2BH,0,40);
	tW2BH.biSize = 40;
	tW2BH.biWidth = width;
	tW2BH.biHeight = height;
	tW2BH.biPlanes = 1;
	tW2BH.biBitCount = 24;
	tW2BH.biCompression = 0;

	out.write((char*)(&tWBFH),14);
	out.write((char*)(&tW2BH),40);
}

//Information on BMP format was provided by www.fileformat.info/format/bmp/egff.htm
void readHeader(istream& in, int& width, int& height){
	BITMAPFILEHEADER tWBFH;
	BITMAPINFOHEADER tW2BH;
	in.read((char*)(&tWBFH),14);
	in.read((char*)(&tW2BH),40);

	width = tW2BH.biWidth;
	height = tW2BH.biHeight;
}

/*****************************************************************************************************/
/**
 * End of provided functions, your work goes below here. You may modify anything below this line, but
 * do NOT modify anything above this line.
 **/


/**
 * Functions for Phase02
 */

const Color WHITE = Color(255,255,255);
const Color BLACK = Color(0,0,0);

/*
 * Purpose: This function should use a BMPCanvas object to create an image of a white square on a black background.
 *          It should then save this image as square256.bmp. 
 * Coloring rule: The pixel at (x,y) should be white only if x >= 64,  x < 192, y >= 64, and y < 192
 */
void MakeSquare256(){
	BMPCanvas myImage("square256", 256, 256); 

	for (int x=0; x<256; x++) {
		for (int y=0; y <256; y++) {
			if ((x >= 64) && (x < 192) && (y >= 64) && (y <192)) {
				myImage.setPixel(x, y, WHITE);
			} else {
				myImage.setPixel(x, y, BLACK);
			}
		}
	}

	myImage.writeBMP();
}


/*
 * Purpose: This function should use a BMPCanvas object to create an image of a "sphere" on a black background.
 *          It should save the image as sphere256.bmp. 
 
 Coloring rule: The center of the sphere will be at (128, 128). 
 The color of the pixel should be given by the following code:

	int distanceSquared = (x-128)*(x-128) + (y-128)*(y-128);
	int color_value = 0;
	if (distanceSquared <= (90*90)){	        
		color_value = (255*((90*90)-distanceSquared))/(90*90);
	}
	Color C = Color(color_value, color_value, color_value);   // Keeping all values the same dictates a shade of grey

 *          In other words, the color starts off white at the center, then falls off linearly with the squared 
 *          distance from the center
 */
void MakeSphere256() {
	BMPCanvas myImage("sphere256", 256, 256);
	
	for (int x=0; x<256; x++) {
		for (int y=0; y <256; y++) {
			int distanceSquared = (x-128)*(x-128) + (y-128)*(y-128);
			int color_value = 0;
			if(distanceSquared <= (90*90)){	        
				color_value = (255*((90*90)-distanceSquared))/(90*90);
			}
			Color c = Color(color_value, color_value, color_value);
			myImage.setPixel(x, y, c);
		}
	}

	myImage.writeBMP();
}

Complex Point2Complex(int i, int j, double reMin, double reMax, int width, double imMin, double imMax, int height) {
	
	double a = reMin + i*(reMax-reMin)/(width - 1.0);
	double b = imMin + j*(imMax-imMin)/(height - 1.0);
	
	return Complex(a,b);
}

int FractalDivergeCount(Complex c, Complex k, int numIterations) {
	Complex z = c;
	for (int i = 0; i < numIterations; i++) {
		if (abs(z) > 2) {
			return i;
		}
		z = z*z + k;
	}
	return numIterations;
}

/*
	This will create the Sierpinski triangle
*/
void Sierpinski(string fileName, int width, int n) {
	cout << "Drawing the Sierpinski Triangle...";
	BMPCanvas canvas(fileName, width, width);

	//Define the three points of the triangle
	int p1x = 0, p1y = 0;
	int p2x = width, p2y = 0;
	int p3x = width / 2, p3y = width;

	//Create variables for the current position and target position
	int currentx, currenty;
	int targetx, targety;

	//Color canvas white
	canvas.blank(true);
	canvas.blank(false);

	//Set color of the triangle - Black in this case
	Color c(255,255,255);

	//Current position is randomly selected
	currentx = randomNumber(0, width+1);
	currenty = randomNumber(0, width+1);

	for(int i = 0; i < n; i++) {
		//Random number 1-3
		int rand = randomNumber(1,4);

		//The target is one of the three points created earlier
		if(rand == 1) {
			targetx = p1x;
			targety = p1y;
		}else if(rand == 2) {
			targetx = p2x;
			targety = p2y;
		}else if(rand == 3) {
			targetx = p3x;
			targety = p3y;
		}

		//current point becomes the midpoint between it and the target point
		currentx = (currentx + targetx) / 2;
		currenty = (currenty + targety) / 2;

		//Color in the midpoint
		canvas.setPixel(currentx, currenty, c); 
	}
	//Write the canvas to file
	canvas.writeBMP();
	cout << "done" << endl;
}

void Julia(string fileName, Complex k) {
	cout << "Drawing the Julia...";
	BMPCanvas canvas(fileName, 1000, 1000);

	//Used in converting point to complex number
	double reMin = -1.5;
	double imMin = -1.5;
	double reMax = 1.6;
	double imMax = 1.6;

	//Ease of use
	Color black(0, 0, 0);
	Color white(255, 255, 255);

	//Used in creating the weird rainbow effect
	double intensity = 0;
	double frequency = 0.3;

	//Iterate through each position on the screen
	for (int x = 0; x < canvas.getWidth(); x++) {
		for (int y = 0; y < canvas.getHeight(); y++) {
			Complex c = Point2Complex(x, y, reMin, reMax, canvas.getWidth(), imMin, imMax, canvas.getHeight());
			int f = FractalDivergeCount(c, k, 100);

			if (f < 100) {
				canvas.setPixel(x, y, black);
			}
			else {
				//Creates some weird inverted rainbow effect
				canvas.setPixel(x, y, Color(sin(frequency*x*y + 0) * 127 + 128, 
											sin(frequency*x*y + 2) * 127 + 128, 
											sin(frequency*x*y + 4) * 127 + 128));
			}
		}
	}
	canvas.writeBMP(); //Write the canvas to file
	cout << "done" << endl;
}

void Mandelbrot(string fileName) {
	cout << "Drawing the Mandelbrot...";
	BMPCanvas canvas(fileName, 1000, 1000);

	//Used in converting point to complex number
	double reMin = -2.0;
	double imMin = -1.5;
	double reMax = 1.0;
	double imMax = 1.5;

	// Used for convenience
	Color black(0, 0, 0);
	Color white(255, 255, 255);
	int intensity = 0;

	for (int x = 0; x < canvas.getWidth(); x++) {
		for (int y = 0; y < canvas.getHeight(); y++) {

			Complex c = Point2Complex(x, y, reMin, reMax, canvas.getWidth(), imMin, imMax, canvas.getHeight()); // Convert point to complex #

			int f = FractalDivergeCount(c, c, 100); // get the diverge count
			intensity = f / 100;
			if (f < 100) { 
				canvas.setPixel(x, y, white); 
			}
			else {
				canvas.setPixel(x, y, Color(255 * intensity, 0, 255 * intensity));
			}
		}
	}
	canvas.writeBMP(); // Write the canvas to file
	cout << "done" << endl;
}


