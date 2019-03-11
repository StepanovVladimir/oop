#include "pch.h"
#include "Functions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

bool PrintArray(const vector<float> &numbers, const string &fileName)
{
	ofstream fOut;
	fOut.open(fileName);
	if (!fOut.is_open())
	{
		return false;
	}

	for (int i = 0; i < numbers.size(); i++)
	{
		ostringstream strm;
		strm << fixed << setprecision(3) << numbers[i];
		fOut << strm.str();
		if (i < numbers.size() - 1)
		{
			fOut << ' ';
		}
	}
	fOut << endl;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		cout << "You have not entered files\n";
		return 1;
	}

	vector<float> numbers;
	
	if (!FillArray(argv[1], numbers))
	{
		cout << "Input error\n";
		return 1;
	}

	ProcessingArray(numbers);

	if (!PrintArray(numbers, argv[2]))
	{
		cout << "Output error\n";
		return 1;
	}

	return 0;
}