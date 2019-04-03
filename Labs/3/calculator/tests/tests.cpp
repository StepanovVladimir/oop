#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../calculator/Storage.h"

using namespace std;

TEST_CASE("Empty storage tests")
{
	CHECK(CStorage::GetVariablesValues() == CStorage::Values{});
	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{});
	try
	{
		CStorage::GetValue("nonexistentName");
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}
}

TEST_CASE("Save undefined var tests")
{
	CStorage::SaveVar("var1");

	CHECK(CStorage::GetVariablesValues() == CStorage::Values{ { "var1", nullopt } });
	CHECK(CStorage::GetValue("var1") == nullopt);

	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{});
}

TEST_CASE("Save var with value tests")
{
	CStorage::SaveVar("var1", 42.f);

	CHECK(CStorage::GetVariablesValues() == CStorage::Values{ { "var1", 42.f } });
	CHECK(CStorage::GetValue("var1") == 42.f);

	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{});
}

TEST_CASE("Save undefined var with with already existing name tests")
{
	try
	{
		CStorage::SaveVar("var1");
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}

	CHECK(CStorage::GetVariablesValues() == CStorage::Values{ { "var1", 42.f } });

	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{});
}

TEST_CASE("Save var with nonexistent identifier tests")
{
	try
	{
		CStorage::SaveVar("var2", "nonexistentName");
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}

	CHECK(CStorage::GetVariablesValues() == CStorage::Values{ { "var1", 42.f } });
	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{});
}

TEST_CASE("Save var with var identifier tests")
{
	CStorage::SaveVar("var2", "var1");
	CStorage::SaveVar("var1", 99.f);

	CHECK(CStorage::GetVariablesValues() == CStorage::Values{
		{ "var1", 99.f },
		{ "var2", 42.f } });

	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{});
}

TEST_CASE("Save func with one nonexistent identifier tests")
{
	try
	{
		CStorage::SaveFunc("func1", "nonexistentName");
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}
	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{});

	CHECK(CStorage::GetVariablesValues() == CStorage::Values{
		{ "var1", 99.f },
		{ "var2", 42.f } });
}

TEST_CASE("Save func with one var identifier tests")
{
	CStorage::SaveVar("var3");
	CStorage::SaveFunc("func1", "var3");

	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{
		{ "func1", nullopt } });
	CHECK(CStorage::GetValue("func1") == nullopt);

	CStorage::SaveVar("var3", 42.f);

	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{
		{ "func1", 42.f } });
	CHECK(CStorage::GetValue("func1") == 42.f);
}

TEST_CASE("Save func with with with already existing name tests")
{
	try
	{
		CStorage::SaveFunc("func1", "var1");
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}

	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{
		{ "func1", 42.f } });
}

TEST_CASE("Save func with one func identifier tests")
{
	CStorage::SaveFunc("func2", "func1");

	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{
		{ "func1", 42.f },
		{ "func2", 42.f } });

	CStorage::SaveVar("var3", 40.f);

	CHECK(CStorage::GetFunctionsValues() == CStorage::Values{
		{ "func1", 40.f },
		{ "func2", 40.f } });
}

TEST_CASE("Save func with addition tests")
{
	CStorage::SaveVar("var4");
	CStorage::SaveFunc("func3", "var3", CFunction::Operation::Add, "var4");

	CHECK(CStorage::GetValue("func3") == nullopt);

	CStorage::SaveVar("var4", 10.f);

	CHECK(CStorage::GetValue("func3") == 50.f);

	try
	{
		CStorage::SaveFunc("func1", "nonexistentName", CFunction::Operation::Add, "var4");
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}
	try
	{
		CStorage::SaveFunc("func1", "var3", CFunction::Operation::Add, "nonexistentName");
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}
}

TEST_CASE("Save func with subtraction tests")
{
	CStorage::SaveFunc("func4", "var3", CFunction::Operation::Sub, "var4");

	CHECK(CStorage::GetValue("func4") == 30.f);
}

TEST_CASE("Save func with multiplication tests")
{
	CStorage::SaveFunc("func5", "var3", CFunction::Operation::Mul, "var4");

	CHECK(CStorage::GetValue("func5") == 400.f);
}

TEST_CASE("Save func with division tests")
{
	CStorage::SaveFunc("func6", "var3", CFunction::Operation::Div, "var4");

	CHECK(CStorage::GetValue("func6") == 4.f);

	CStorage::SaveVar("var4", 0.f);

	try
	{
		CStorage::GetValue("func6");
		CHECK(false);
	}
	catch (const string &)
	{
		CHECK(true);
	}
}