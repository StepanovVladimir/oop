#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

bool StringIsNumber(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return false;
		}
	}
	return true;
}

unsigned char GetReverseByte(unsigned char byte)
{
	const char BITS_OF_BYTE[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
	const int NUMBER_OF_BITS = 8;
	unsigned char reverseByte = 0;
	for (int i = 0; i < NUMBER_OF_BITS; i++)
	{
		if ((byte & BITS_OF_BYTE[i]) != 0)
		{
			reverseByte = reverseByte | BITS_OF_BYTE[NUMBER_OF_BITS - 1 - i];
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

	if (str == "" || str.length() > 3 || !StringIsNumber(str))
	{
		cout << "You entered not byte\n";
		return 1;
	}

	int number = stoi(str);

	if (number > 255)
	{
		cout << "You entered not byte\n";
		return 1;
	}
	
	cout << (unsigned)GetReverseByte(number) << endl;

	return 0;
}