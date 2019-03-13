#include "pch.h"
#include "Reader.h"
#include <iostream>
#include <fstream>

void AddRecord(const string &word, const string &translation, map<string, vector<string>> &dictionary, vector<string> &words)
{
	dictionary[word].push_back(translation);
	dictionary[translation].push_back(word);

	words.push_back(word);
	words.push_back(translation);
}

bool FillDictionary(const string &fileName, map<string, vector<string>> &dictionary, vector<string> &words)
{
	ifstream fIn;
	fIn.open(fileName);
	if (!fIn.is_open())
	{
		return false;
	}

	string word, translation;
	while (getline(fIn, word))
	{
		if (getline(fIn, translation))
		{
			AddRecord(word, translation, dictionary, words);
		}
		else
		{
			break;
		}
	}
	return true;
}