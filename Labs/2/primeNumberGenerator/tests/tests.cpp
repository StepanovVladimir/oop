#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../primeNumberGenerator/Generator.h"

TEST_CASE("StrToNumber tests")
{
	int number;
	CHECK(StrToNumber("abc", number) == false);
	CHECK(StrToNumber("1000000000", number) == false);
	StrToNumber("-2", number);
	CHECK(number == -2);
	StrToNumber("123", number);
	CHECK(number == 123);
}

TEST_CASE("GetPrimeBoolVector tests")
{
	CHECK(GetPrimeBoolVector(-4) == vector<bool>{});
	CHECK(GetPrimeBoolVector(1) == vector<bool>{});
	CHECK(GetPrimeBoolVector(8) == vector<bool>{ false, false, true, true, false, true, false, true, false });
}

TEST_CASE("BoolVectorToSet tests")
{
	CHECK(BoolVectorToIntSet(vector<bool>{}) == set<int>{});
	CHECK(BoolVectorToIntSet(vector<bool>{ false, false, true, true, false, true, false }) == set<int>{ 2, 3, 5 });
}

TEST_CASE("GeneratePrimeNumbersSet tests")
{
	CHECK(GeneratePrimeNumbersSet(20) == set<int>{ 2, 3, 5, 7, 11, 13, 17, 19 });

#ifdef NDEBUG

	CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);

#endif
}