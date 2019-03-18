#pragma once

#include <set>
#include <string>
#include <optional>
#include <vector>

using namespace std;

bool StrToNumber(const string &str, int &number);
vector<bool> GetPrimeBoolVector(int upperBound);
set<int> BoolVectorToSet(const vector<bool> &arePrimeNumbers);
set<int> GeneratePrimeNumbersSet(int upperBound);
optional<set<int>> GetPrimeNumbersSet(const string &str);