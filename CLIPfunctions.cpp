#include "CLIPheader.h"
#include<fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

int extractFileExtension(string fileName);

//constructors
Image::Image(string fileName)
{
	ifstream fin(fileName);
	if(!fin)
	{
		cout <<"File error opening file. Select a correct filename"<<endl;
		exit(1);
	}
	
	getline(fin,fileFormat);
	string lineRead;

	//cols and rows with or w/o comment
	fin >> lineRead;
	if(lineRead[0] == '#')
	{
		getline(fin,lineRead);
		fin >> xpix >> ypix;
	}
	else
	{
		int extractedDigit = 0;
		int i = 0;
		while (lineRead[i] != '\0')
		{
			extractedDigit *= 10;
			extractedDigit += (int)(lineRead[i] - '0');
			i++;
		}
		xpix = extractedDigit;
		fin >> ypix;
	}
	imageComment = "#Pauls Image Morphology Project";

	fin >> grayScaleMax;

	image = new int*[ypix];
	for(int i = 0; i < ypix; i++)
		image[i] = new int[xpix];

	convertedImage = new int*[ypix];
		for(int i = 0; i < ypix; i++)
			convertedImage[i] = new int[xpix];
		
	
	//the original image is now stored in the 2D array image
	for(int r = 0; r < ypix; r++)
		for(int c = 0; c < xpix; c++)
			fin >> image[r][c];
		
}
Binary::Binary(string fileName):Image(fileName)
{
	int newYpix = getYpix();
	int newXpix = getXpix();

	binaryImage = new int*[newYpix];
	for(int i = 0; i < newYpix; i++)
		binaryImage[i] = new int[newXpix];
	//if its already a binary -- dont convert it again
	if(extractFileExtension(fileName) == 1)
	{
		int **OGimage = image;
		//converts to binary
		for(int r = 0; r < newYpix; r++)
		{
			for(int c = 0; c < newXpix; c++)
			{
				if(OGimage[r][c] < threshold)
					binaryImage[r][c] = 1;
				else
					binaryImage[r][c] = 0;
			}
		}
	}
	else if(extractFileExtension(fileName) == 0)
	{
		int **OGimage = image;
		for(int r = 0; r < newYpix; r++)
			for(int c = 0; c < newXpix; c++)
					binaryImage[r][c] = OGimage[r][c];
	}
	convertedImage = new int*[newYpix];
	for(int i = 0; i < newYpix; i++)
		convertedImage[i] = new int[newXpix];

	for(int r = 0; r < newYpix; r++)
		for(int c = 0; c < newXpix; c++)
			convertedImage[r][c] = binaryImage[r][c];

}
int extractFileExtension(string fileName)
{
	int i = 0;
	string fileExtension;
	while(fileName[i] != '.')
		i++;
	
	while(fileName[i] != '\0')
	{
		fileExtension += fileName[i];
		i++;
	}
	if(fileExtension == ".pgm")
		return 1;
	else if(fileExtension == ".pbm")
		return 0;

}
GrayScale::GrayScale(string fileName):Image(fileName)
{
	histogramArray = new int[(getMaxGrayLevel()/25)+1];
	for(int i = 0; i < (getMaxGrayLevel()/25)+1;i++)
		histogramArray[i] = 0;
	grayScaleFileName = fileName;
	xpix = getXpix();
	ypix = getYpix();
}

//Image functions
void Image::normalOutput()
{
	cout << "Writing file normalOutput.pgm..." << endl;

	string alteredImage = "normalOutput.pgm";

	ofstream fout(alteredImage);
	if(!fout) // fin.fail()
	{
		cout <<"Fatal File operation Failure";
		exit(1);
	}
	fout << fileFormat << endl;
	fout << imageComment << endl;
	fout << xpix << " " << ypix << endl;
	fout << grayScaleMax <<  endl;

	for(int r = 0; r < ypix; ++r)
	{
		for(int c = 0; c < xpix; ++c)
			fout << image[r][c] << " ";
		fout << endl;
	}

	cout << "Finished writing file normalOutput.pgm." << endl << endl;
}

void Image::convertedOutput(string outFileName)
{
	cout << "Writing file " << outFileName << endl;

	string alteredImage = outFileName;

	ofstream fout(alteredImage);
	if(!fout) // fin.fail()
	{
		cout <<"Fatal File operation Failure";
		exit(1);
	}
	fout << fileFormat << endl;
	fout << imageComment << endl;
	fout << xpix << " " << ypix << endl;
	fout << grayScaleMax <<  endl;

	for(int r = 0; r < ypix; ++r)
	{
		for(int c = 0; c < xpix; ++c)
			fout << convertedImage[r][c] << " ";
		fout << endl;
	}

	cout << "Finished writing file " << outFileName << endl << endl;
}

void Image::rotateImage(int rotationState)
{
	cout << "Rotating image ... " << endl;
	if(rotationState == 1)
	{//90 degrees CW
		
		int newYpix = ypix;
		setYpix(xpix);
		setXpix(newYpix);

		//reset image oriantation
		delete [] convertedImage;

		convertedImage = new int*[ypix];
		for(int i = 0; i < ypix; i++)
			convertedImage[i] = new int[xpix];

		for(int j = 0, ii = xpix-1; j < xpix; j++, ii--)
			for(int i = 0, jj = 0; i < ypix; i++, jj++)
 				convertedImage[jj][ii] = image[j][i];
	}
	else if(rotationState == 2)
	{//180 degrees

		for(int j = 0, jj = ypix-1; j < ypix; j++, jj--)
			for(int i = 0, ii = xpix-1; i < xpix; i++, ii--)
				convertedImage[jj][ii] = image[j][i];
	}
	else if(rotationState == 3)
	{//270 degrees CW 
		int newYpix = ypix;
		setYpix(xpix);
		setXpix(newYpix);

		//reset image oriantation
		delete [] convertedImage;

		convertedImage = new int*[ypix];
		for(int i = 0; i < ypix; i++)
			convertedImage[i] = new int[xpix];

		for(int j = 0, ii = 0; j < xpix; j++, ii++)
			for(int i = 0, jj = ypix-1; i < ypix; i++, jj--)
 				convertedImage[jj][ii] = image[j][i];
	}
	else
		cout << "Please enter a valid selection (1 - 90-deg  2 - 180-deg  or  3 - 270-deg (clockwise))" << endl;
	cout << "Image rotated" << endl << endl;
}

void Image::resizeImage(int sizeState)
{
	cout << "Resizing image ... " << endl;
	if(sizeState == 1)
	{//half-size
		setYpix(ypix/2);
		setXpix(xpix/2);

		//reset size
		delete [] convertedImage;

		convertedImage = new int*[ypix];
		for(int i = 0; i < ypix; i++)
			convertedImage[i] = new int[xpix];

		int skipCol = 1;
		int skipRow = 1;
		for(int r = 0; r < ypix*2; r++)
		{
			if(skipRow == 1)
			{
				for(int c = 0; c < xpix*2; c++)
				{
					if(skipCol == 1)
					{
						convertedImage[r/2][c/2] = image[r][c];
						skipCol = 0;
					}
					else
						skipCol = 1;
				}
				skipCol = 1;
				skipRow = 0;
			}
			else
				skipRow = 1;
		}
		
	}
	else if(sizeState == 2)
	{//double-size

		setYpix(ypix*2);
		setXpix(xpix*2);

		//reset size
		delete [] convertedImage;

		convertedImage = new int*[ypix];
		for(int i = 0; i < ypix; i++)
			convertedImage[i] = new int[xpix];

		for(int r = 0; r < ypix; r++)
		{
			for(int c = 0; c < xpix; c++)
				convertedImage[r][c] = image[r/2][c/2];
		}
	}
	else
		cout << "Please enter a valid selection (1 - half-size  or  2 - double-size" << endl;
	cout << "Image resized" << endl << endl;
}

//Binary functions
void Binary::dilate()
{
	cout << "Dilating image..." << endl;
	for(int r = 1; r < ((getYpix())-1);r++)
		for(int c = 1; c < ((getXpix())-1);c++)
		{
			if(convertedImage[r][c] == 0)
				if(dilateAroundOrigin(r,c) == 1)
					convertedImage[r][c] = 1;
		}

	cout<< "Image dilated..." << endl << endl;
}

int Binary::dilateAroundOrigin(int ycoor, int xcoor)
{
	//using a 3 x 3 structuring element with origin at center
	int r = (ycoor - 1), c = (xcoor - 1), dilate = 0;
	
	for(int rr = 0; rr < 3; rr++,r++)
		for(int cc = 0, c = (xcoor - 1); cc < 3; cc++,c++)
			if(binaryImage[r][c] == 1)
				if(binaryImage[ycoor][xcoor] == 0)
					dilate = 1;
			
	return dilate;
}

void Binary::erode()
{
	cout << "Eroding image..." << endl;
	for(int r = 1; r < ((getYpix())-1);r++)
		for(int c = 1; c < ((getXpix())-1);c++)
		{
			if(convertedImage[r][c] == 1)
				if(erodeAroundOrigin(r,c) == 0)
					convertedImage[r][c] = 0;
		}

	cout<< "Image eroded..." << endl << endl;
}

int Binary::erodeAroundOrigin(int ycoor, int xcoor)
{
	//3x3 structuring element
	
	/*
	int r = (ycoor - 1), c = (xcoor - 1), erode = 1;
	for(int rr = 0; rr < 3; rr++,r++)
	{
		for(int cc = 0, c = (xcoor - 1); cc < 3; cc++,c++)
		{
			if(binaryImage[r][c] == 0)
			{
				if(binaryImage[ycoor][xcoor] == 1)
					erode = 0;
			}
		}
	}
	*/

	//cross shaped structuring element
	
	int r = ycoor, c = xcoor, erode = 1;
	if(binaryImage[ycoor][xcoor] == 1)
	{
		if(binaryImage[(r-1)][c] == 0)
			erode = 0;
		else if(binaryImage[r][(c+1)] == 0)
			erode = 0;
		else if(binaryImage[(r+1)][c] == 0)
			erode = 0;
		else if(binaryImage[r][(c-1)] == 0)
			erode = 0;
	}

	return erode;
}

void Binary::normalBinaryOut()
{
	cout << "Writing file normalBinaryOutput.pbm..." << endl;

	string alteredImage = "normalBinaryOutput.pbm";

	ofstream fout(alteredImage);
	if(!fout) // fin.fail()
	{
		cout <<"Fatal File operation Failure";
		exit(1);
	}
	fout << "P1" << endl;
	fout << getImageComment() << endl;
	fout << getXpix() << " " << getYpix() << endl;

	for(int r = 0; r < getYpix(); ++r)
	{
		for(int c = 0; c < getXpix(); ++c)
			fout << binaryImage[r][c] << " ";
		fout << endl;
	}

	cout << "Finished writing file normalBinaryOutput.pbm." << endl << endl;
}

void Binary::convertedBinaryOut(string alteredImage)
{

	
	cout << "Writing file "<< alteredImage<< endl;


	ofstream fout(alteredImage);
	if(!fout) // fin.fail()
	{
		cout <<"Fatal File operation Failure";
		exit(1);
	}
	fout << "P1" << endl;
	fout << getImageComment() << endl;
	fout << getXpix() << " " << getYpix() << endl;

	for(int r = 0; r < getYpix(); r++)
	{
		for(int c = 0; c < getXpix(); c++)
			fout << convertedImage[r][c] << " ";
		fout << endl;
	}

	cout << "Finished writing file " << alteredImage << endl << endl;
}

//Grayscale functions
void GrayScale::histogram()
{
	cout << "Compiling Histogram data ..." << endl;
	for(int r = 0; r < getYpix(); r++)
	{
		for(int c = 0; c < getXpix(); c++)
		{
			checkPixel = image[r][c];
	
			if(checkPixel < 26)
				histogramArray[0]++;
			else if(checkPixel < 51)
				histogramArray[1]++;
			else if(checkPixel < 76)
				histogramArray[2]++;
			else if(checkPixel < 101)
				histogramArray[3]++;
			else if(checkPixel < 126)
				histogramArray[4]++;
			else if(checkPixel < 151)
				histogramArray[5]++;
			else if(checkPixel < 176)
				histogramArray[6]++;
			else if(checkPixel < 201)
				histogramArray[7]++;
			else if(checkPixel < 226)
				histogramArray[8]++;
			else if(checkPixel < 256)
				histogramArray[9]++;
		}
	}
	cout << "Histogram compiled" << endl << endl;
}

void GrayScale::printHistogram()
{
	cout << "Histogram for: " << grayScaleFileName << endl << endl;
	double totalPixels = ((double)xpix * (double)ypix);
	cout << "Total pixels: " << totalPixels << endl;
	
	cout <<(((double)histogramArray[0]/totalPixels)*100) << "% or " << histogramArray[0] 
		<< " pixels are from 0 - 25" << endl
	 <<(((double)histogramArray[1]/totalPixels)*100) << "% or " << histogramArray[1] 
		<< " pixels from 26 - 50" << endl
	 <<(((double)histogramArray[2]/totalPixels)*100) << "% or " << histogramArray[2] 
		<< " pixels from 51 - 75" << endl
	 <<(((double)histogramArray[3]/totalPixels)*100) << "% or " << histogramArray[3] 
		<< " pixels from 76 - 100" << endl
	 <<(((double)histogramArray[4]/totalPixels)*100) << "% or " << histogramArray[4] 
		<< " pixels from 101 - 125" << endl
	 <<(((double)histogramArray[5]/totalPixels)*100) << "% or " << histogramArray[5] 
		<< " pixels from 126 - 150" << endl
	 <<(((double)histogramArray[6]/totalPixels)*100) << "% or " << histogramArray[6] 
		<< " pixels from 151 - 175" << endl
	 <<(((double)histogramArray[7]/totalPixels)*100) << "% or " << histogramArray[7] 
		<< " pixels from 176 - 200" << endl
	 <<(((double)histogramArray[8]/totalPixels)*100) << "% or " << histogramArray[8]
		<< " pixels from 201 - 225" << endl
	 <<(((double)histogramArray[9]/totalPixels)*100) << "% or " << histogramArray[9] 
		<< " pixels from 226 - 256" << endl << endl;
}

void GrayScale::colorize(int colorSelection)
{
	cout << "Colorizing image... " << endl;
	string newFormat = "P3";
	setFileFormat(newFormat);

	delete [] convertedImage;

	convertedImage = new int*[ypix];
	for(int i = 0; i < ypix; i++)
		convertedImage[i] = new int[xpix * 3];
	
	
		int colorState = 0;
		for(int r = 0; r < ypix; r++)
		{
			for(int c = 0; c < xpix * 3; c++)
			{
				//red chromatic
				if(colorSelection == 1)
				{
					if(colorState == 0)
					{
						//red pixel
						convertedImage[r][c] = 255;
						colorState = 1;
					}
					else if(colorState == 1)
					{
						//green pixel
						convertedImage[r][c] = image[r][c/3];
						colorState = 2;
					}
					else if(colorState == 2)
					{
						//blue pixel
						convertedImage[r][c] = image[r][c/3];
						colorState = 0;
					}
				}
				//green chromatic
				else if(colorSelection == 2)
				{		
					if(colorState == 0)
					{
						//red pixel
						convertedImage[r][c] =  image[r][c/3];
						colorState = 1;
					}
					else if(colorState == 1)
					{
						//green pixel
						convertedImage[r][c] = 255;
						colorState = 2;
					}
					else if(colorState == 2)
					{
						//blue pixel
						convertedImage[r][c] = image[r][c/3];
						colorState = 0;
					}
			
				}
				//blue chromatic
				else if(colorSelection == 3)
				{
	
					if(colorState == 0)
					{
						//red pixel
						convertedImage[r][c] = image[r][c/3];
						colorState = 1;
					}
					else if(colorState == 1)
					{
						//green pixel
						convertedImage[r][c] = image[r][c/3];
						colorState = 2;
					}
					else if(colorState == 2)
					{
						//blue pixel
						convertedImage[r][c] = 255;
						colorState = 0;
					}
				}
				else
					cout << "Please provide a valid entry (1 - red 2 - green 3 - blue )";
				
			}
		}
		cout << "Image colorized" << endl << endl;
	}	

void GrayScale::colorizedOutput(string outFileName)
{
	cout << "Writing file " << outFileName << endl;

	string alteredImage = outFileName;

	ofstream fout(alteredImage);
	if(!fout) // fin.fail()
	{
		cout <<"Fatal File operation Failure";
		exit(1);
	}
	fout << fileFormat << endl;
	fout << imageComment << endl;
	fout << xpix << " " << ypix << endl;
	fout << grayScaleMax <<  endl;

	for(int r = 0; r < ypix; ++r)
	{
		for(int c = 0; c < xpix * 3; ++c)
			fout << convertedImage[r][c] << " ";
		fout << endl;
	}

	cout << "Finished writing file " << outFileName << endl << endl;
}
