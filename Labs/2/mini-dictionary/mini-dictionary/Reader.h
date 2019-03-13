#pragma once

#include <map>
#include <vector>
#include <string>

using namespace std;

void AddRecord(const string &word, const string &translation, map<string, vector<string>> &dictionary, vector<string> &words);
bool FillDictionary(const string &fileName, map<string, vector<string>> &dictionary, vector<string> &words);