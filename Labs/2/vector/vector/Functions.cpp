#include "pch.h"
#include "Functions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

bool FillArray(const string &fileName, vector<float> &numbers)
{
	ifstream fIn;
	fIn.open(fileName);
	if (!fIn.is_open())
	{
		return false;
	}

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
	if (numbers.size() == 0)
	{
		return 0;
	}

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
	sort(numbers.begin(), numbers.end());
}