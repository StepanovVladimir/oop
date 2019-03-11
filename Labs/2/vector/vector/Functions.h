#pragma once

#include <vector>
#include <string>

using namespace std;

bool FillArray(const string &fileName, vector<float> &numbers);
float FindMin(const vector<float> &numbers);
void MultiplyArray(vector<float> &numbers, float multiplier);
void ProcessingArray(vector<float> &numbers);