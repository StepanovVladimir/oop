#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string GetChangedStr(const string& str, const string& searchStr, const string& replaceStr)
{
	string changedStr;
	size_t index = 0;
	size_t foundIndex;
	while (index < str.length())
	{
		foundIndex = str.find(searchStr, index);
		if (foundIndex != string::npos && searchStr != "")
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

bool CopyWithReplace(const string &inFileName, const string &outFileName, const string &searchStr, const string &replaceStr)
{
	ifstream fIn;
	ofstream fOut;
	fIn.open(inFileName);
	fOut.open(outFileName);
	if (!fIn.is_open() || !fOut.is_open())
	{
		return false;
	}

	string str;
	while (getline(fIn, str))
	{
		fOut << GetChangedStr(str, searchStr, replaceStr);
		if (!fIn.eof())
		{
			fOut << endl;
		}
	}
	return true;
}

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		cout << "Not all arguments are specified\n";
		return 1;
	}

	if (!CopyWithReplace(argv[1], argv[2], argv[3], argv[4]))
	{
		cout << "Failed to open files\n";
		return 1;
	}

	return 0;
}