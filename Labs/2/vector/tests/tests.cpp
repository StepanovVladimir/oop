#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../vector/Functions.h"

TEST_CASE("FillArray tests")
{
	vector<float> numbers;

	SECTION("Errors in input")
	{
		CHECK(FillArray("lalala", numbers) == false);
		CHECK(FillArray("badInput.txt", numbers) == false);
	}
	
	SECTION("Empty input")
	{
		CHECK(FillArray("empty.txt", numbers) == true);
		CHECK(numbers == vector<float>{});
	}

	SECTION("Good input")
	{
		CHECK(FillArray("input.txt", numbers) == true);
		CHECK(numbers == vector<float>{ 6.43f, 3.f, 1.43f, -5.43f, -2.f, 4.34f });
	}
}

TEST_CASE("FindMin tests")
{
	CHECK(FindMin(vector<float>{}) == 0.f);
	CHECK(FindMin(vector<float>{ 6.43f, 3.43f, 1.43f, 5.43f, 2.64f, 4.34f }) == 1.43f);
	CHECK(FindMin(vector<float>{ 6.43f, 3.43f, 1.43f, -5.43f, -2.64f, 4.34f }) == -5.43f);
}

TEST_CASE("MultiplyArray tests")
{
	SECTION("Empty array")
	{
		vector<float> numbers;
		MultiplyArray(numbers, 4.f);
		CHECK(numbers == vector<float>{});
	}

	SECTION("Multiply by zero")
	{
		vector<float> numbers = { 6.43f, 3.43f, 1.43f, -5.43f, -2.64f, 4.34f };
		MultiplyArray(numbers, 0.f);
		CHECK(numbers == vector<float>{ 0, 0, 0, 0, 0, 0});
	}

	SECTION("Multiply by positive")
	{
		vector<float> numbers = { 6.43f, 3.43f, 1.43f, -5.43f, -2.64f, 4.34f };
		MultiplyArray(numbers, 4.f);
		CHECK(numbers == vector<float>{ 25.72f, 13.72f, 5.72f, -21.72f, -10.56f, 17.36f});
	}

	SECTION("Multiply by negative")
	{
		vector<float> numbers = { 6.43f, 3.43f, 1.43f, -5.43f, -2.64f, 4.34f };
		MultiplyArray(numbers, -4.f);
		CHECK(numbers == vector<float>{ -25.72f, -13.72f, -5.72f, 21.72f, 10.56f, -17.36f});
	}
}

TEST_CASE("ProcessingArray tests")
{
	SECTION("Empty array")
	{
		vector<float> numbers;
		ProcessingArray(numbers);
		CHECK(numbers == vector<float>{});
	}

	SECTION("Not empty array")
	{
		vector<float> numbers = { 6.f, 3.f, 1.f, -5.f, -2.f, 4.f };
		ProcessingArray(numbers);
		CHECK(numbers == vector<float>{ -30.f, -20.f, -15.f, -5.f, 10.f, 25.f });
	}
}