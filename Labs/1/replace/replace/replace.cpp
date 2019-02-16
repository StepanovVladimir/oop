#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string GetChangedStr(const string& str, const string& searchStr, const string& replaceStr)
{
	string changedStr;
	int index = 0;
	int foundIndex;
	while (index < str.length())
	{
		foundIndex = str.find(searchStr, index);
		if (foundIndex != -1 && searchStr.length() > 0)
		{
			changedStr.append(str, index, foundIndex - index);
			changedStr.append(replaceStr);
			index = foundIndex + searchStr.length();
		}
		else
		{
			changedStr.append(str, index);
			break;
		}
	}
	return changedStr;
}

void CopyWithReplace(istream &fIn, ostream &fOut, const string &searchStr, const string &replaceStr)
{
	string str;
	while (getline(fIn, str))
	{
		fOut << GetChangedStr(str, searchStr, replaceStr);
		if (!fIn.eof())
		{
			fOut << endl;
		}
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

	CopyWithReplace(fIn, fOut, searchStr, replaceStr);

	return 0;
}