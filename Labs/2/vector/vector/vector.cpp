#include "pch.h"
#include "ArrayHandler.h"
#include <iostream>
#include <sstream>
#include <iomanip>

bool FillArray(vector<float> &numbers)
{
	string str;
	float f;
	cin >> str;
	while (!cin.eof())
	{
		istringstream strm(str);
		strm >> f;
		if (!strm)
		{
			return false;
		}
		numbers.push_back(f);
		cin >> str;
	}
	return true;
}

void PrintArray(const vector<float> &numbers)
{
	for (int i = 0; i < numbers.size(); i++)
	{
		ostringstream strm;
		strm << fixed << setprecision(3) << numbers[i];
		cout << strm.str();
		if (i < numbers.size() - 1)
		{
			cout << ' ';
		}
	}
	cout << endl;
}

int main()
{
	vector<float> numbers;

	if (!FillArray(numbers))
	{
		cout << "Input error\n";
		return 1;
	}

	ProcessingArray(numbers);
	PrintArray(numbers);

	return 0;
}