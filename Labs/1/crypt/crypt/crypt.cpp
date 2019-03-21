#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

const uint8_t MAX_BYTE = 255;
const string CRYPT = "crypt";
const string DECRYPT = "decrypt";
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

bool StrToByte(const string &str, uint8_t &byte)
{
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

bool Encrypt(const string &inFileName, const string &outFileName, uint8_t key)
{
	ifstream fIn;
	ofstream fOut;
	fIn.open(inFileName);
	fOut.open(outFileName);
	if (!fIn.is_open() || !fOut.is_open())
	{
		return false;
	}

	char byte;
	uint8_t encryptedByte;
	while (fIn.get(byte))
	{
		byte ^= key;
		encryptedByte = MixingBits(byte);
		fOut << encryptedByte;
	}
	return true;
}

uint8_t MixingBitsBack(uint8_t byte)
{
	uint8_t decryptedByte = 0;
	for (int i = 0; i < NUMBER_OF_BITS; i++)
	{
		if ((byte & BIT_MASK[1 << i]) != 0)
		{
			decryptedByte |= 1 << i;
		}
	}
	return decryptedByte;
}

bool Decrypt(const string &inFileName, const string &outFileName, uint8_t key)
{
	ifstream fIn;
	ofstream fOut;
	fIn.open(inFileName);
	fOut.open(outFileName);
	if (!fIn.is_open() || !fOut.is_open())
	{
		return false;
	}

	char byte;
	uint8_t decryptedByte;
	while (fIn.get(byte))
	{
		decryptedByte = MixingBitsBack(byte);
		decryptedByte ^= key;
		fOut << decryptedByte;
	}
	return true;
}

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		cout << "Not all arguments are specified.\n";
		cout << "The command line must be in the following format:\n";
		cout << "crypt.exe <command> <input file> <output file> <key>\n";
		return 1;
	}

	uint8_t key;
	if (!StrToByte(argv[4], key))
	{
		cout << "You entered not number from 0 to 255\n";
		return 1;
	}

	if (argv[1] == CRYPT)
	{
		if (!Encrypt(argv[2], argv[3], key))
		{
			cout << "Failed to open files\n";
			return 1;
		}
	}
	else if (argv[1] == DECRYPT)
	{
		if (!Decrypt(argv[2], argv[3], key))
		{
			cout << "Failed to open files\n";
			return 1;
		}
	}
	else
	{
		cout << "You entered not 'crypt' or 'decrypt'\n";
		return 1;
	}

	return 0;
}
