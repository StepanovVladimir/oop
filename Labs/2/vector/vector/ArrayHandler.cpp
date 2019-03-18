#include "pch.h"
#include "ArrayHandler.h"
#include <sstream>
#include <algorithm>

void MultiplyArray(vector<float> &numbers, float multiplier)
{
	for (float &number : numbers)
	{
		number *= multiplier;
	}
}

void ProcessingArray(vector<float> &numbers)
{
	if (numbers.size() > 0)
	{
		auto iter = min_element(begin(numbers), end(numbers));
		float min = numbers[distance(begin(numbers), iter)];
		MultiplyArray(numbers, min);
	}
}