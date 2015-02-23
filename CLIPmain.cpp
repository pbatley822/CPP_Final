#include "CLIPheader.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

int main(void)
{
	cout <<
			"*********************************\n"
			"*****____________________********\n"
			"**** Welcome to C.L.I.P.P. ******"
			"\n****_______________________******"
			"\n* brought to you by Paul Batley *\n"
			"**_____________________________**"
			"\n**                             **"
			"\n*********************************\n\n";
	while(true)
	{
		cout << "What do you want to do?"<<endl<<endl
			<<"1  -  Read in an image" << endl
			<<"2  -  Rotate an image" << endl
			<<"3  -  Resize an image  " << endl
			<<"4  -  Erode an image" << endl
			<<"5  -  Dilate an image" << endl
			<<"6  -  Show histogram (*.pgm)" << endl
			<<"7  -  Display an image" << endl
			<<"8  -  Colorize an image(*.pgm)" << endl
			<<"9  -  ???" << endl
			<<"10 -  Exit" << endl;
		int fate;
		cin >> fate;

		
		if(fate == 1)
		{
			string inputFileName;
			cout << "Please select an image to read in" << endl;
			cout << "1 - baboon_ascii.pgm | 2 - casablanca_ascii.pgm | 3 - read your own file" << endl;
			int imageSelection;
			cin >> imageSelection;
			if(imageSelection == 1)
			{
				inputFileName = "baboon_ascii.pgm";
			}
			else if(imageSelection == 2)
			{
				inputFileName = "casablanca_ascii.pgm";
			}
			else if(imageSelection == 3)
			{
				cout << "Please enter a file name to read in: "; 
				cin >> inputFileName;
			}
			Image i1(inputFileName);
			i1.normalOutput();
		}
		else if(fate == 2)
		{
			string inputFileName;
			cout << "Please select file to rotate" << endl;
			cout << "1 - baboon_ascii.pgm | 2 - casablanca_ascii.pgm | 3 - read your own file" << endl;
			int imageSelection;
			cin >> imageSelection;
			if(imageSelection == 1)
			{
				inputFileName = "baboon_ascii.pgm";
			}
			else if(imageSelection == 2)
			{
				inputFileName = "casablanca_ascii.pgm";
			}
			else if(imageSelection == 3)
			{
				cout << "Please input a pgm file name to rotate: ";
				cin >> inputFileName;
			}
			Image i2(inputFileName);
			cout << "Please input your desired rotation(1 -- 90 | 2 -- 180 | 3 -- 270)" << endl;
			int rotationSelection;
			cin >> rotationSelection;
			i2.rotateImage(rotationSelection);
			cout << "Please input a file name(*.pgm) to use for the output file: ";
			string outFileName;
			cin >> outFileName;
			i2.convertedOutput(outFileName);
			
		}
		else if(fate == 3)
		{
			string inputFileName;
			cout << "Please input a pgm file name to resize" << endl;
			cout << "1 - baboon_ascii.pgm | 2 - casablanca_ascii.pgm | 3 - read your own file" << endl;
			int imageSelection;
			cin >> imageSelection;
			if(imageSelection == 1)
			{
				inputFileName = "baboon_ascii.pgm";
			}
			else if(imageSelection == 2)
			{
				inputFileName = "casablanca_ascii.pgm";
			}
			else if(imageSelection == 3)
			{
				cout << "Please enter a file name to resize: ";
				cin >> inputFileName;
			}
			Image i3(inputFileName);
			cout << "Please input your resize selection(1 -- half-size | 2 -- double-size)" << endl;
			int reSizeSelection;
			cin >> reSizeSelection;
			i3.resizeImage(reSizeSelection);
			cout << "Please input a file name(*.pgm) to use for the output file: ";
			string outFileName;
			cin >> outFileName;
			i3.convertedOutput(outFileName);
			
		}
		else if(fate == 4)
		{
			string inputFileName;
			cout << "Please input a pgm file name to erode" << endl;
			cout << "1 - baboon_ascii.pgm | 2 - casablanca_ascii.pgm | 3 - read your own file(*.pgm)" << endl;
			int imageSelection;
			cin >> imageSelection;
			if(imageSelection == 1)
			{
				inputFileName = "baboon_ascii.pgm";
			}
			else if(imageSelection == 2)
			{
				inputFileName = "casablanca_ascii.pgm";
			}
			else if(imageSelection == 3)
			{
				cout << "Please enter a file name to erode: ";
				cin >> inputFileName;
			}
			Binary b1(inputFileName);	
			b1.erode();
			string outputFileName;
			cout << "Please input a pgm file name for output: ";
			cin >> outputFileName;
			b1.convertedBinaryOut(outputFileName);
		}
		else if(fate == 5)
		{
			string inputFileName;
			cout << "Please input a pgm file name to dilate" << endl;
			cout << "1 - baboon_ascii.pgm | 2 - casablanca_ascii.pgm | 3 - read your own file" << endl;
			int imageSelection;
			cin >> imageSelection;
			if(imageSelection == 1)
			{
				inputFileName = "baboon_ascii.pgm";
			}
			else if(imageSelection == 2)
			{
				inputFileName = "casablanca_ascii.pgm";
			}
			else if(imageSelection == 3)
			{
				cout <<"Please enter a *.pgm file to dilate: ";
				cin >> inputFileName;
			}
			Binary b2(inputFileName);	
			b2.dilate();
			string outputFileName;
			cout << "Please enter a file name to for the output file: ";
			cin >> outputFileName;
			b2.convertedBinaryOut(outputFileName);
		}
		else if(fate == 6)
		{
			string inputFileName;
			cout << "Please input a pgm file name to display the histogram for" << endl;
			cout << "1 - baboon_ascii.pgm | 2 - casablanca_ascii.pgm | 3 - read your own file" << endl;
			int imageSelection;
			cin >> imageSelection;
			if(imageSelection == 1)
			{
				inputFileName = "baboon_ascii.pgm";
			}
			else if(imageSelection == 2)
			{
				inputFileName = "casablanca_ascii.pgm";
			}
			else if(imageSelection == 3)
			{
				cout << "Please enter a file name to show the histogram for: ";
				cin >> inputFileName;
			}
			GrayScale g1(inputFileName);
			g1.histogram();
			g1.printHistogram();
		}
		else if(fate == 7)
		{
			string fileToDisplay;
			cout <<"Enter a file to display" << endl;
			cin >> fileToDisplay;
			cout << "Displaying image..."<<endl;
			system(fileToDisplay.c_str());
			cout<<"Image dispalyed..."<<endl;
		}
		else if(fate == 8)
		{
			string grayImage;
			cout << "Enter a grayscale image to colorize" << endl;
			cin >> grayImage;
			GrayScale c1(grayImage);
			int colorSelection;
			cout << "Enter a color selection: (1 - red | 2 - green | 3 - blue)" << endl;
			cin >> colorSelection;
			c1.colorize(colorSelection);
			string outImage;
			cout << "Enter a file name for output" << endl;
			cin >> outImage;
			c1.colorizedOutput(outImage);
		}
		else if(fate == 9)
		{
			cout << "selecting an image for random processing" << endl;
			Image r1("baboon_ascii.pgm");
			cout << "Performing operations on baboon_ascii.pgm" << endl;
			//rotates 270 degrees CW
			r1.rotateImage(3);
			string op1 = "operation1.pgm";
			r1.convertedOutput(op1);
			Image r2(op1);
			//halves image
			r2.resizeImage(1);
			string op2 = "operation2.pgm";
			r2.convertedOutput(op2);
			GrayScale r3(op2);
			r3.histogram();
			r3.printHistogram();
			Binary r4(op2);
			r4.normalBinaryOut();
			r4.erode();
			string op3 = "operation3.pbm";
			r4.convertedBinaryOut(op3);
			GrayScale r5(op2);
			//make it green
			r5.colorize(2);
			string op4 ="operation4.ppm";
			r5.colorizedOutput(op4);
			cout<<"Displaying "<< op4 <<endl;
			system(op4.c_str());
		}
		else if(fate == 10)
			break;
		else
			cout << "Not quite there yet" << endl;

	}
	system("pause");
	return 0;
}