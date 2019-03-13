#include "pch.h"
#include "Reader.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void PrintTranslations(const vector<string> &translations)
{
	for (int i = 0; i < translations.size(); i++)
	{
		cout << translations[i];
		if (i < translations.size() - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}

void RewriteDictionary(const vector<string> &words, const string &fileName)
{
	ofstream fOut;
	if (fileName != "")
	{
		fOut.open(fileName);
	}
	else
	{
		fOut.open("dictionary.txt");
	}

	for (int i = 0; i < words.size(); i++)
	{
		fOut << words[i] << endl;
	}
}

void FinishDialog(bool dictionaryChanged, const vector<string> &words, const string &fileName)
{
	if (dictionaryChanged)
	{
		string str;
		cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n>";
		getline(cin, str);
		if (str == "y" || str == "Y")
		{
			RewriteDictionary(words, fileName);
			cout << "Изменения сохранены. До свидания.\n";
		}
		else
		{
			cout << "Изменения не сохранены. До свидания.\n";
		}
	}
	else
	{
		cout << "До свидания.\n";
	}
}

void ConductDialog(map<string, vector<string>> &dictionary, vector<string> &words, const string &fileName)
{
	bool dictionaryChanged = false;
	string word, translation;
	while (true)
	{
		cout << '>';
		getline(cin, word);
		if (word == "...")
		{
			FinishDialog(dictionaryChanged, words, fileName);
			break;
		}
		transform(word.begin(), word.end(), word.begin(), tolower);
		auto iter = dictionary.find(word);
		if (iter != dictionary.end())
		{
			PrintTranslations(iter -> second);
		}
		else
		{
			cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа.\n>";
			getline(cin, translation);
			if (translation == "...")
			{
				FinishDialog(dictionaryChanged, words, fileName);
				break;
			}

			if (translation != "")
			{
				transform(translation.begin(), translation.end(), translation.begin(), tolower);
				AddRecord(word, translation, dictionary, words);
				dictionaryChanged = true;
				cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\".\n";
			}
			else
			{
				cout << "Слово \"" << word << "\" проигнорировано.\n";
			}
		}
	}
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");

	map<string, vector<string>> dictionary;
	vector<string> words;
	string fileName;

	if (argc > 1)
	{
		fileName = argv[1];
		if (!FillDictionary(fileName, dictionary, words))
		{
			fileName = "";
		}
	}
	else
	{
		fileName = "";
	}

	ConductDialog(dictionary, words, fileName);

	return 0;
}