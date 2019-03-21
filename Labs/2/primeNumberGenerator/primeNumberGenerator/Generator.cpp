#include "pch.h"
#include "Generator.h"
#include <iostream>

const int MAX_UPPER_BOUND = 100000000;

bool StrToNumber(const string &str, int &number)
{
	try
	{
		number = stoi(str);
	}
	catch (const invalid_argument &)
	{
		return false;
	}
	catch (const out_of_range &)
	{
		return false;
	}

	if (number > MAX_UPPER_BOUND)
	{
		return false;
	}
	return true;
}

vector<bool> GetPrimeBoolVector(int upperBound)
{
	if (upperBound < 2)
	{
		return vector<bool>{};
	}
	vector<bool> arePrimeNumbers(upperBound + 1, true);
	size_t maxDivider = (int)sqrt(arePrimeNumbers.size());
	for (size_t i = 2; i <= maxDivider; i++)
	{
		if (arePrimeNumbers[i])
		{
			for (size_t j = 2; i * j < arePrimeNumbers.size(); j++)
			{
				arePrimeNumbers[i * j] = false;
			}
		}
	}
	return arePrimeNumbers;
}

set<int> BoolVectorToSet(const vector<bool> &arePrimeNumbers)
{
	set<int> primeNumbers;
	for (size_t i = 2; i < arePrimeNumbers.size(); i++)
	{
		if (arePrimeNumbers[i])
		{
			primeNumbers.insert(i);
		}
	}
	return primeNumbers;
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> arePrimeNumbers = GetPrimeBoolVector(upperBound);
	return BoolVectorToSet(arePrimeNumbers);
}

optional<set<int>> GetPrimeNumbersSet(const string &str)
{
	int upperBound;
	if (!StrToNumber(str, upperBound))
	{
		return nullopt;
	}
	return GeneratePrimeNumbersSet(upperBound);
}
