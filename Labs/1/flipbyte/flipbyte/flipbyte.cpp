#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

uint8_t GetReverseByte(uint8_t byte)
{
	const int NUMBER_OF_BITS = 8;
	const uint8_t BIT_MASK = 0x01;
	uint8_t reverseByte = 0;
	for (int i = 0; i < NUMBER_OF_BITS; i++)
	{
		if ((byte & (BIT_MASK << i)) != 0)
		{
			reverseByte = reverseByte | (BIT_MASK << NUMBER_OF_BITS - 1 - i);
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

	string str;
	str = argv[1];
	int number;

	try
	{
		number = stoi(str);
	}
	catch (const invalid_argument &err)
	{
		cout << "You entered not byte\n";
		return 1;
	}
	catch (const out_of_range &err)
	{
		cout << "You entered not byte\n";
		return 1;
	}

	if (number > 255)
	{
		cout << "You entered not byte\n";
		return 1;
	}
	
	cout << (unsigned)GetReverseByte(number) << endl;

	return 0;
}