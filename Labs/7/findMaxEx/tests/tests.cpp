#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../findMaxEx/Finder.h"
#include "../findMaxEx/Sportsman.h"

using namespace std;

bool LessInt(int i1, int i2)
{
	return i1 < i2;
}

bool LessIntByAbs(int i1, int i2)
{
	return abs(i1) < abs(i2);
}

TEST_CASE("Find max int tests")
{
	vector<int> arr{ 2, 1, -3, -1 };

	int maxInt;
	FindMax(arr, maxInt, LessInt);
	CHECK(maxInt == 2);

	int maxIntByAbs;
	FindMax(arr, maxIntByAbs, LessIntByAbs);
	CHECK(maxIntByAbs == -3);
}

TEST_CASE("Find max sportsman tests")
{
	vector<Sportsman> sportsmans{
		{ "Alexander", "Ivanov", 172, 73 },
		{ "Alexey", "Smirnov", 176, 85 },
		{ "Andrey", "Kuznetsov", 185, 72 }
	};

	Sportsman sportsmanWithMaxHeight;
	FindMax(sportsmans, sportsmanWithMaxHeight, LessByHeight);
	CHECK(sportsmanWithMaxHeight.firstName == "Andrey");
	CHECK(sportsmanWithMaxHeight.lastName == "Kuznetsov");
	CHECK(sportsmanWithMaxHeight.height == 185);
	CHECK(sportsmanWithMaxHeight.weight == 72);

	Sportsman sportsmanWithMaxWeight;
	FindMax(sportsmans, sportsmanWithMaxWeight, LessByWeight);
	CHECK(sportsmanWithMaxWeight.firstName == "Alexey");
	CHECK(sportsmanWithMaxWeight.lastName == "Smirnov");
	CHECK(sportsmanWithMaxWeight.height == 176);
	CHECK(sportsmanWithMaxWeight.weight == 85);
}