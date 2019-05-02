#pragma once

#include <string>

struct Sportsman
{
	std::string firstName;
	std::string lastName;
	unsigned height;
	unsigned weight;
};

bool LessByHeight(Sportsman i1, Sportsman i2);
bool LessByWeight(Sportsman i1, Sportsman i2);