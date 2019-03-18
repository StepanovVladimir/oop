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

	optional<set<int>> primeNumbers = GetPrimeNumbersSet(argv[1]);

	if (!primeNumbers)
	{
		cout << "Unexpected argument";
		return 1;
	}

	PrintSet(primeNumbers.value());

	return 0;
}