#include "pch.h"
#include "Generator.h"
#include <iostream>

void PrintSet(const set<int> &intSet)
{
	for (auto iter = intSet.begin(); iter != intSet.end(); iter++)
	{
		cout << *iter;
		if (iter != --intSet.end())
		{
			cout << ' ';
		}
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "You have not entered a number\n";
		return 1;
	}

	int upperBound;
	if (!StrToNumber(argv[1], upperBound))
	{
		cout << "Unexpected argument";
		return 1;
	}

	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	PrintSet(primeNumbers);

	return 0;
}