#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../myString/MyString.h"
#include <sstream>

using namespace std;

TEST_CASE("Constructor tests")
{
	CMyString myString1;
	CHECK(myString1.GetLength() == 0);
	CHECK(myString1.GetStringData() == string());

	CMyString myString2("abc");
	CHECK(myString2.GetLength() == 3);
	CHECK(myString2.GetStringData() == string("abc"));

	CMyString myString3("abcdef", 3);
	CHECK(myString3.GetLength() == 3);
	CHECK(myString3.GetStringData() == string("abc"));

	CMyString myString4("abc\0def", 7);
	CHECK(myString4.GetLength() == 7);
	CHECK(myString4.GetStringData() == string("abc"));

	CMyString myString5(myString2);
	CHECK(myString5.GetLength() == 3);
	CHECK(myString5.GetStringData() == string("abc"));

	CMyString myString6(string("abc"));
	CHECK(myString6.GetLength() == 3);
	CHECK(myString6.GetStringData() == string("abc"));
}

TEST_CASE("SubString tests")
{
	CMyString myString("abcdefghi");
	CHECK(myString.SubString(3).GetStringData() == string("defghi"));
	CHECK(myString.SubString(3, 3).GetStringData() == string("def"));

	CHECK_THROWS_AS(myString.SubString(9), runtime_error);
}

TEST_CASE("Clear tests")
{
	CMyString myString("abc");
	myString.Clear();
	CHECK(myString.GetLength() == 0);
	CHECK(myString.GetStringData() == string());
}

TEST_CASE("Operator '=' tests")
{
	CMyString myString = CMyString("abc");
	CHECK(myString.GetLength() == 3);
	CHECK(myString.GetStringData() == string("abc"));

	myString = myString;
	CHECK(myString.GetLength() == 3);
	CHECK(myString.GetStringData() == string("abc"));
}

TEST_CASE("Operator '+=' tests")
{
	CMyString myString1("abc");
	myString1 += CMyString("def");
	CHECK(myString1.GetLength() == 6);
	CHECK(myString1.GetStringData() == string("abcdef"));

	CMyString myString2("abc");
	myString2 += myString2;
	CHECK(myString2.GetLength() == 6);
	CHECK(myString2.GetStringData() == string("abcabc"));
}

TEST_CASE("Operator '+' tests")
{
	CMyString myString1 = CMyString("abc") + CMyString("def");
	CHECK(myString1.GetLength() == 6);
	CHECK(myString1.GetStringData() == string("abcdef"));

	CMyString myString2 = CMyString("abc") + string("def");
	CHECK(myString2.GetLength() == 6);
	CHECK(myString2.GetStringData() == string("abcdef"));

	CMyString myString3 = string("abc") + CMyString("def");
	CHECK(myString3.GetLength() == 6);
	CHECK(myString3.GetStringData() == string("abcdef"));

	CMyString myString4 = CMyString("abc") + "def";
	CHECK(myString4.GetLength() == 6);
	CHECK(myString4.GetStringData() == string("abcdef"));

	CMyString myString5 = "abc" + CMyString("def");
	CHECK(myString5.GetLength() == 6);
	CHECK(myString5.GetStringData() == string("abcdef"));
}

TEST_CASE("Operator '[]' tests")
{
	CMyString myString("abc");
	CHECK(myString[1] == 'b');

	myString[1] = 'x';
	CHECK(myString.GetStringData() == string("axc"));

	CHECK_THROWS_AS(myString[3], runtime_error);
}

TEST_CASE("Operator '==' tests")
{
	CHECK(CMyString("abc") == CMyString("abc"));
	CHECK_FALSE(CMyString("abc") == CMyString("ab"));
	CHECK_FALSE(CMyString("abc") == CMyString("abd"));
}

TEST_CASE("Operator '!=' tests")
{
	CHECK(CMyString("abc") != CMyString("ab"));
	CHECK(CMyString("abc") != CMyString("abd"));
	CHECK_FALSE(CMyString("abc") != CMyString("abc"));
}

TEST_CASE("Operator '<' tests")
{
	CHECK(CMyString("abc") < CMyString("b"));
	CHECK(CMyString("abc") < CMyString("abcd"));

	CHECK_FALSE(CMyString("abc") < CMyString("abc"));
	CHECK_FALSE(CMyString("b") < CMyString("abc"));
	CHECK_FALSE(CMyString("abcd") < CMyString("abc"));
}

TEST_CASE("Operator '>' tests")
{
	CHECK(CMyString("b") > CMyString("abc"));
	CHECK(CMyString("abcd") > CMyString("abc"));

	CHECK_FALSE(CMyString("abc") > CMyString("abc"));
	CHECK_FALSE(CMyString("abc") > CMyString("b"));
	CHECK_FALSE(CMyString("abc") > CMyString("abcd"));
}

TEST_CASE("Operator '<=' tests")
{
	CHECK(CMyString("abc") <= CMyString("b"));
	CHECK(CMyString("abc") <= CMyString("abcd"));
	CHECK(CMyString("abc") <= CMyString("abc"));

	CHECK_FALSE(CMyString("b") <= CMyString("abc"));
	CHECK_FALSE(CMyString("abcd") <= CMyString("abc"));
}

TEST_CASE("Operator '>=' tests")
{
	CHECK(CMyString("b") >= CMyString("abc"));
	CHECK(CMyString("abcd") >= CMyString("abc"));
	CHECK(CMyString("abc") >= CMyString("abc"));

	CHECK_FALSE(CMyString("abc") >= CMyString("b"));
	CHECK_FALSE(CMyString("abc") >= CMyString("abcd"));
}

TEST_CASE("Operator '<<' tests")
{
	ostringstream outStrm;
	CMyString myString("abc");
	outStrm << myString;
	CHECK(outStrm.str() == "abc");
}

TEST_CASE("Operator '>>' tests")
{
	istringstream inStrm("abc");
	CMyString myString;
	inStrm >> myString;
	CHECK(myString == "abc");
}