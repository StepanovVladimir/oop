#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

const int NUMBER_OF_BITS = 8;
map<uint8_t, uint8_t> BIT_MASK = {
		{1, 1 << 2},
		{1 << 1, 1 << 3},
		{1 << 2, 1 << 4},
		{1 << 3, 1 << 6},
		{1 << 4, 1 << 7},
		{1 << 5, 1},
		{1 << 6, 1 << 1},
		{1 << 7, 1 << 5}
};

uint8_t MixingBits(uint8_t byte)
{
	uint8_t encryptedByte = 0;
	for (int i = 0; i < NUMBER_OF_BITS; i++)
	{
		if ((byte & (1 << i)) != 0)
		{
			encryptedByte |= BIT_MASK[1 << i];
		}
	}
	return encryptedByte;
}

void Encrypt(istream &fIn, ostream &fOut, uint8_t key)
{
	char byte;
	uint8_t encryptedByte;
	while (fIn.get(byte))
	{
		byte ^= key;
		encryptedByte = MixingBits(byte);
		fOut << encryptedByte;
	}
}

uint8_t MixingBitsBack(uint8_t byte)
{
	uint8_t encryptedByte = 0;
	for (int i = 0; i < NUMBER_OF_BITS; i++)
	{
		if ((byte & BIT_MASK[1 << i]) != 0)
		{
			encryptedByte |= 1 << i;
		}
	}
	return encryptedByte;
}

void Decrypt(istream &fIn, ostream &fOut, uint8_t key)
{
	char byte;
	uint8_t decryptedByte;
	while (fIn.get(byte))
	{
		decryptedByte = MixingBitsBack(byte);
		decryptedByte ^= key;
		fOut << decryptedByte;
	}
}

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		cout << "Not all arguments are specified\n";
		return 1;
	}

	ifstream fIn;
	ofstream fOut;
	fIn.open(argv[2]);
	fOut.open(argv[3]);

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

	int number;
	try
	{
		number = stoi(argv[4]);
	}
	catch (const invalid_argument &err)
	{
		cout << "You entered not number from 0 to 255\n";
		return 1;
	}
	catch (const out_of_range &err)
	{
		cout << "You entered not number from 0 to 255\n";
		return 1;
	}

	if (number > 255)
	{
		cout << "You entered not number from 0 to 255\n";
		return 1;
	}

	string command = argv[1];
	if (command == "crypt")
	{
		Encrypt(fIn, fOut, number);
	}
	else if (command == "decrypt")
	{
		Decrypt(fIn, fOut, number);
	}
	else
	{
		cout << "You entered not 'crypt' or 'decrypt'\n";
		return 1;
	}

	return 0;
}