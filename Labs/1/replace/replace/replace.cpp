#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void CopyFile(ifstream &fIn, ofstream &fOut)
{
	string str;
	while (!fIn.eof())
	{
		getline(fIn, str);
		fOut << str;
		if (!fIn.eof())
		{
			fOut << endl;
		}
	}
}

void FillStr(ifstream &fIn, string &str, int lenOfstr)
{
	char ch;
	str = "";
	for (int i = 0; i < lenOfstr; i++)
	{
		fIn.get(ch);
		if (!fIn.eof())
		{
			str = str + ch;
		}
		else
		{
			break;
		}
	}
}

void MoveWindow(ifstream &fIn, ofstream &fOut, string &str)
{
	char ch;
	fIn.get(ch);
	if (!fIn.eof())
	{
		fOut << str[0];
		for (int i = 0; i < str.length() - 1; i++)
		{
			str[i] = str[i + 1];
		}
		str[str.length() - 1] = ch;
	}
}

void CopyWithReplace(ifstream &fIn, ofstream &fOut, string searchStr, string replaceStr)
{
	string str;
	FillStr(fIn, str, searchStr.length());
	while (!fIn.eof())
	{
		if (str == searchStr)
		{
			fOut << replaceStr;
			FillStr(fIn, str, searchStr.length());
		}
		else
		{
			MoveWindow(fIn, fOut, str);
		}
	}
	fOut << str;
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
	string searchStr, replaceStr;

	fIn.open(argv[1]);
	fOut.open(argv[2]);
	searchStr = argv[3];
	replaceStr = argv[4];

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

	if (searchStr == "")
	{
		CopyFile(fIn, fOut);
	}
	else
	{
		CopyWithReplace(fIn, fOut, searchStr, replaceStr);
	}

	return 0;
}