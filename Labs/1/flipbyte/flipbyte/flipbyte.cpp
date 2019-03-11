#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

bool StrToByte(const string &str, uint8_t &byte)
{
	const uint8_t MAX_BYTE = 255;

	int number;
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

	if (number > MAX_BYTE)
	{
		return false;
	}

	byte = number;
	return true;
}

uint8_t GetReverseByte(uint8_t byte)
{
	const int NUMBER_OF_BITS = 8;

	uint8_t reverseByte = 0;
	for (int i = 0; i < NUMBER_OF_BITS; i++)
	{
		if ((byte & (1 << i)) != 0)
		{
			reverseByte |= (1 << (NUMBER_OF_BITS - 1 - i));
		}
	}
	return reverseByte;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "You have not entered a byte\n";
		return 1;
	}

	uint8_t byte;
	if (!StrToByte(argv[1], byte))
	{
		cout << "You entered not byte\n";
		return 1;
	}

	cout << (unsigned)GetReverseByte(byte) << endl;

	return 0;
}