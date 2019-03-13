#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../mini-dictionary/Reader.h"

TEST_CASE("AddRecord tests")
{
	setlocale(LC_ALL, "Russian");

	map<string, vector<string>> dictionary;
	vector<string> words;

	AddRecord("cat", "кот", dictionary, words);
	map<string, vector<string>> resultDictionary = {
		{ "cat", vector<string>{ "кот" } },
		{ "кот", vector<string>{ "cat" } }
	};
	REQUIRE(dictionary == resultDictionary);
	REQUIRE(words == vector<string>{ "cat", "кот" });

	AddRecord("cat", "кошка", dictionary, words);
	resultDictionary = {
		{ "cat", vector<string>{ "кот", "кошка" } },
		{ "кот", vector<string>{ "cat" } },
		{ "кошка", vector<string>{ "cat" } }
	};
	REQUIRE(dictionary == resultDictionary);
	REQUIRE(words == vector<string>{ "cat", "кот", "cat", "кошка" });

	AddRecord("ball", "мяч", dictionary, words);
	resultDictionary = {
		{ "cat", vector<string>{ "кот", "кошка" } },
		{ "кот", vector<string>{ "cat" } },
		{ "кошка", vector<string>{ "cat" } },
	    { "ball", vector<string>{ "мяч" } },
	    { "мяч", vector<string>{ "ball" } }
	};
	REQUIRE(dictionary == resultDictionary);
	REQUIRE(words == vector<string>{ "cat", "кот", "cat", "кошка", "ball", "мяч" });
}

TEST_CASE("FillDictionary tests")
{
	setlocale(LC_ALL, "Russian");

	map<string, vector<string>> dictionary;
	vector<string> words;

	SECTION("Failed file")
	{
		CHECK(FillDictionary("lalala", dictionary, words) == false);
		CHECK(dictionary == map<string, vector<string>>{});
		CHECK(words == vector<string>{});
	}

	SECTION("Good file")
	{
		CHECK(FillDictionary("dictionary.txt", dictionary, words) == true);
		map<string, vector<string>> resultDictionary = {
			{ "cat", vector<string>{ "кот", "кошка" } },
			{ "кот", vector<string>{ "cat" } },
			{ "кошка", vector<string>{ "cat" } },
			{ "ball", vector<string>{ "мяч" } },
			{ "мяч", vector<string>{ "ball" } }
		};
		CHECK(dictionary == resultDictionary);
		CHECK(words == vector<string>{ "cat", "кот", "cat", "кошка", "ball", "мяч" });
	}
}