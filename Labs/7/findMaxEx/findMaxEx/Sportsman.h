#pragma once

#include <string>

struct Sportsman
{
	std::string firstName;
	std::string lastName;
	unsigned height;
	unsigned weight;
};

bool LessByHeight(const Sportsman &sportsman1, const Sportsman &sportsman2);
bool LessByWeight(const Sportsman &sportsman1, const Sportsman &sportsman2);