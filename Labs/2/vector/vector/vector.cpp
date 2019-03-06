#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

bool FillArray(istream &fIn, vector<float> &numbers)
{
	string str;
	float f;
	fIn >> str;
	while (!fIn.eof())
	{
		istringstream strm(str);
		strm >> f;
		if (!strm)
		{
			return false;
		}
		numbers.push_back(f);
		fIn >> str;
	}
	return true;
}

float FindMin(const vector<float> &numbers)
{
	float min = numbers[0];
	for (int i = 1; i < numbers.size(); i++)
	{
		if (min > numbers[i])
		{
			min = numbers[i];
		}
	}
	return min;
}

void MultiplyArray(vector<float> &numbers, float multiplier)
{
	for (int i = 0; i < numbers.size(); i++)
	{
		numbers[i] *= multiplier;
	}
}

void ProcessingArray(vector<float> &numbers)
{
	float min = FindMin(numbers);
	MultiplyArray(numbers, min);
}

void PrintArray(const vector<float> &numbers, ostream &fOut)
{
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

	ifstream fIn;
	ofstream fOut;
	fIn.open(argv[1]);
	fOut.open(argv[2]);

	if (!fIn.is_open())
	{
		cout << "Failed to open input file\n";
		return 1;
	}
	if (!fOut.is_open())
	{
		cout << "Failed to open output file\n";
		return 1;
	}

	vector<float> numbers;

	if (!FillArray(fIn, numbers))
	{
		cout << "Input error\n";
		return 1;
	}

	if (numbers.size() > 0)
	{
		ProcessingArray(numbers);
	}

	sort(numbers.begin(), numbers.end());
	PrintArray(numbers, fOut);

	return 0;
}