#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../stringList/StringList.h"

using namespace std;

TEST_CASE("Default constructor tests")
{
	CStringList list;

	CHECK(list.IsEmpty());
	CHECK(list.GetSize() == 0);
	CHECK(list.begin() == list.end());

	CHECK_THROWS_AS(*list.begin(), runtime_error);
	CHECK_THROWS_AS(++list.begin(), runtime_error);
	CHECK_THROWS_AS(--list.begin(), runtime_error);
}

TEST_CASE("PushFront tests")
{
	CStringList list;

	list.PushFront("1");
	CHECK(*list.begin() == "1");

	list.PushFront("2");
	CHECK(*list.begin() == "2");

	list.PushFront("3");
	CHECK(*list.begin() == "3");

	CHECK_FALSE(list.IsEmpty());
	CHECK(list.GetSize() == 3);
	CHECK(list.begin() != list.end());

	string result;
	for (const string &str : list)
	{
		result += str;
	}
	CHECK(result == "321");
}

TEST_CASE("PushBack tests")
{
	CStringList list;

	list.PushBack("1");
	list.PushBack("2");
	list.PushBack("3");

	CHECK_FALSE(list.IsEmpty());
	CHECK(list.GetSize() == 3);

	string result;
	for (const string &str : list)
	{
		result += str;
	}
	CHECK(result == "123");
}

TEST_CASE("Clear tests")
{
	CStringList list;

	list.PushBack("1");
	list.PushBack("2");
	list.PushBack("3");

	list.Clear();

	CHECK(list.IsEmpty());
	CHECK(list.GetSize() == 0);
	CHECK(list.begin() == list.end());
}

TEST_CASE("Copy constructor tests")
{
	CStringList list1;

	list1.PushBack("1");
	list1.PushBack("2");
	list1.PushBack("3");

	CStringList list2(list1);

	CHECK_FALSE(list2.IsEmpty());
	CHECK(list2.GetSize() == 3);

	string result;
	for (const string &str : list2)
	{
		result += str;
	}
	CHECK(result == "123");
}

TEST_CASE("Operator '=' tests")
{
	CStringList list1;

	list1.PushBack("1");
	list1.PushBack("2");
	list1.PushBack("3");

	CStringList list2 = list1;

	CHECK_FALSE(list2.IsEmpty());
	CHECK(list2.GetSize() == 3);

	string result;
	for (const string &str : list2)
	{
		result += str;
	}
	CHECK(result == "123");

	list2 = list2;

	CHECK_FALSE(list2.IsEmpty());
	CHECK(list2.GetSize() == 3);

	result = "";
	for (const string &str : list2)
	{
		result += str;
	}
	CHECK(result == "123");
}

TEST_CASE("Moving constructor tests")
{
	CStringList list1;

	list1.PushBack("1");
	list1.PushBack("2");
	list1.PushBack("3");

	CStringList list2(move(list1));

	CHECK(list1.IsEmpty());
	CHECK(list1.GetSize() == 0);
	CHECK(list1.begin() == list1.end());

	CHECK_FALSE(list2.IsEmpty());
	CHECK(list2.GetSize() == 3);

	string result;
	for (const string &str : list2)
	{
		result += str;
	}
	CHECK(result == "123");
}

TEST_CASE("Moving operator '=' tests")
{
	CStringList list1;

	list1.PushBack("1");
	list1.PushBack("2");
	list1.PushBack("3");

	CStringList list2 = move(list1);

	CHECK(list1.IsEmpty());
	CHECK(list1.GetSize() == 0);
	CHECK(list1.begin() == list1.end());

	CHECK_FALSE(list2.IsEmpty());
	CHECK(list2.GetSize() == 3);

	string result;
	for (const string &str : list2)
	{
		result += str;
	}
	CHECK(result == "123");

	list2 = move(list2);

	CHECK_FALSE(list2.IsEmpty());
	CHECK(list2.GetSize() == 3);

	result = "";
	for (const string &str : list2)
	{
		result += str;
	}
	CHECK(result == "123");
}

TEST_CASE("Empty iterator tests")
{
	CStringList::CIterator iter;

	CHECK_THROWS_AS(*iter, runtime_error);
	CHECK_THROWS_AS(++iter, runtime_error);
	CHECK_THROWS_AS(--iter, runtime_error);
}

TEST_CASE("Iterators tests")
{
	CStringList list;

	list.PushBack("1");
	list.PushBack("2");
	list.PushBack("3");

	CHECK_THROWS_AS(--list.begin(), runtime_error);
	CHECK_THROWS_AS(*list.end(), runtime_error);
	CHECK_THROWS_AS(++list.end(), runtime_error);

	CHECK(*(++list.begin()) == "2");
	CHECK(*(--list.end()) == "3");

	auto iter = list.begin();

	CHECK(*(iter++) == "1");
	CHECK(*iter == "2");

	CHECK(*(iter--) == "2");
	CHECK(*iter == "1");

	CHECK(*list.cbegin() == "1");
	CHECK_THROWS_AS(*list.cend(), runtime_error);
}

TEST_CASE("Reverse iterators tests")
{
	CStringList list;

	list.PushBack("1");
	list.PushBack("2");
	list.PushBack("3");

	CHECK_THROWS_AS(++list.rbegin(), runtime_error);
	CHECK_THROWS_AS(*list.rend(), runtime_error);
	CHECK_THROWS_AS(--list.rend(), runtime_error);

	CHECK(*(--list.rbegin()) == "2");
	CHECK(*(++list.rend()) == "3");

	auto iter = list.rbegin();

	CHECK(*(iter--) == "1");
	CHECK(*iter == "2");

	CHECK(*(iter++) == "2");
	CHECK(*iter == "1");

	CHECK(*list.crbegin() == "1");
	CHECK_THROWS_AS(*list.crend(), runtime_error);
}

TEST_CASE("Insert tests")
{
	CStringList list;

	list.PushBack("1");
	list.PushBack("2");
	list.PushBack("3");

	list.Insert(list.begin(), "4");

	CHECK(list.GetSize() == 4);
	CHECK(*list.begin() == "4");

	list.Insert(list.end(), "5");

	CHECK(list.GetSize() == 5);
	CHECK(*(--list.end()) == "5");

	list.Insert(++list.begin(), "6");

	CHECK(list.GetSize() == 6);
	CHECK(*(++list.begin()) == "6");

	string result;
	for (const string &str : list)
	{
		result += str;
	}
	CHECK(result == "461235");
}

TEST_CASE("Erase tests")
{
	CStringList list;

	list.PushBack("1");
	list.PushBack("2");
	list.PushBack("3");

	auto beginIter = list.begin();
	auto endIter = list.end();

	list.Erase(beginIter);

	CHECK(list.GetSize() == 2);
	CHECK(*list.begin() == "2");

	CHECK_THROWS_AS(list.Erase(endIter), runtime_error);

	list.Erase(--endIter);

	CHECK(list.GetSize() == 1);
	CHECK(*(--list.end()) == "2");

	string result;
	for (const string &str : list)
	{
		result += str;
	}
	CHECK(result == "2");
}