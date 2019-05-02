#pragma once

#include <vector>
#include <algorithm>

template<typename T, typename Less>
bool FindMax(const std::vector<T> &arr, T &maxValue, const Less &less)
{
	if (arr.size() == 0)
	{
		return false;
	}
	auto iter = std::max_element(arr.cbegin(), arr.cend(), less);
	maxValue = *iter;
	return true;
}