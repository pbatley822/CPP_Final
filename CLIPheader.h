#ifndef CLIPHEADER_H_
#define CLIPHEADER_H_

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

class Image
{
	protected:
		int **image;
		int **convertedImage;
		int xpix;
		int ypix;
		int grayScaleMax;
		string fileFormat;
		string imageComment;
		string imageName;
	public:
		int getYpix(){return ypix;}
		int setYpix(int newY){return ypix = newY;}
		int getXpix(){return xpix;}
		int setXpix(int newX){return xpix = newX;}
		string getFileFormat(){return fileFormat;}
		string setFileFormat(string newFormat){return fileFormat = newFormat;}
		string getImageComment(){return imageComment;}
		int getMaxGrayLevel(){return grayScaleMax;}
		Image(string fileName);
		~Image(){delete [] image; delete [] convertedImage;}
		void normalOutput();
		void resizeImage(int sizeState);
		void rotateImage(int rotationState);
		//void pixilize();
		void convertedOutput(string outFileName);
};

class Binary: public Image
{
	private: 
		static const int threshold = 127;
		int **binaryImage;
		int **convertedImage;
		string inputFileName;
	public:
		Binary(string fileName);
		~Binary(){delete [] binaryImage; delete [] convertedImage;}
		void dilate();
		void erode();
		int dilateAroundOrigin(int ycoor, int xcoor);
		int erodeAroundOrigin(int ycoor, int xcoor);
		void convertedBinaryOut(string alteredImage);
		void normalBinaryOut();
};

class GrayScale: public Image
{	
	private: 
		int *histogramArray;
		int xpix, ypix;
		int grayMax;
		int checkPixel;
		string grayScaleFileName;
	public:
		void histogram();
		GrayScale(string fileName);
		~GrayScale(){delete [] histogramArray;}
		void printHistogram();
		void colorize(int colorSelection);
		void colorizedOutput(string fileName);
};

#endif