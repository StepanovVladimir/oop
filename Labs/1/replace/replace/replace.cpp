#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string ReplaceStr(const string& str, const string& searchStr, const string& replaceStr)
{
	int index = 0;
	string result;
	while (index < str.length())
	{
		int foundIndex = str.find(searchStr, index);
		if (foundIndex != -1 && searchStr.length() > 0)
		{
			result.append(str, index, foundIndex - index);
			result.append(replaceStr);
			index = foundIndex + searchStr.length();
		}
		else
		{
			result.append(str, index);
			break;
		}
	}
	return result;
}

void CopyWithReplace(istream &fIn, ostream &fOut, const string &searchStr, const string &replaceStr)
{
	string str;
	while (getline(fIn, str))
	{
		fOut << ReplaceStr(str, searchStr, replaceStr);
		if (!fIn.eof())
		{
			fOut << '\n';
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