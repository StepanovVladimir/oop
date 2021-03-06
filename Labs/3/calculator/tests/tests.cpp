#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../calculator/Calculator.h"

using namespace std;

TEST_CASE("Empty storage tests")
{
	CCalculator calculator;
	CHECK(calculator.GetVariablesValues() == CCalculator::Values{});
	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{});
	try
	{
		calculator.GetValue("nonexistentName");
		CHECK(false);
	}
	catch (const runtime_error &)
	{
		CHECK(true);
	}
}

TEST_CASE("Save undefined var tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1");

	CHECK(calculator.GetVariablesValues() == CCalculator::Values{ { "var1", nullopt } });
	CHECK(calculator.GetValue("var1") == nullopt);

	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{});
}

TEST_CASE("Save var with value tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1", 42.f);

	CHECK(calculator.GetVariablesValues() == CCalculator::Values{ { "var1", 42.f } });
	CHECK(calculator.GetValue("var1") == 42.f);

	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{});
}

TEST_CASE("Save undefined var with with already existing name tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1", 42.f);
	try
	{
		calculator.SaveVar("var1");
		CHECK(false);
	}
	catch (const runtime_error &)
	{
		CHECK(true);
	}

	CHECK(calculator.GetVariablesValues() == CCalculator::Values{ { "var1", 42.f } });

	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{});
}

TEST_CASE("Save var with nonexistent identifier tests")
{
	CCalculator calculator;
	try
	{
		calculator.SaveVar("var1", "nonexistentName");
		CHECK(false);
	}
	catch (const runtime_error &)
	{
		CHECK(true);
	}

	CHECK(calculator.GetVariablesValues() == CCalculator::Values{});
	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{});
}

TEST_CASE("Save var with var identifier tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1", 42.f);
	calculator.SaveVar("var2", "var1");
	calculator.SaveVar("var1", 99.f);

	CHECK(calculator.GetVariablesValues() == CCalculator::Values{
		{ "var1", 99.f },
		{ "var2", 42.f } });

	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{});
}

TEST_CASE("Save func with one nonexistent identifier tests")
{
	CCalculator calculator;
	try
	{
		calculator.SaveFunc("func1", "nonexistentName");
		CHECK(false);
	}
	catch (const runtime_error &)
	{
		CHECK(true);
	}
	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{});
}

TEST_CASE("Save func with one var identifier tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1");
	calculator.SaveFunc("func1", "var1");

	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{
		{ "func1", nullopt } });
	CHECK(calculator.GetValue("func1") == nullopt);

	calculator.SaveVar("var1", 42.f);

	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{
		{ "func1", 42.f } });
	CHECK(calculator.GetValue("func1") == 42.f);
}

TEST_CASE("Save func with with with already existing name tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1", 42.f);
	calculator.SaveFunc("func1", "var1");
	try
	{
		calculator.SaveFunc("func1", "var1");
		CHECK(false);
	}
	catch (const runtime_error &)
	{
		CHECK(true);
	}

	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{
		{ "func1", 42.f } });
}

TEST_CASE("Save func with one func identifier tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1", 42.f);
	calculator.SaveFunc("func1", "var1");
	calculator.SaveFunc("func2", "func1");

	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{
		{ "func1", 42.f },
		{ "func2", 42.f } });

	calculator.SaveVar("var1", 40.f);

	CHECK(calculator.GetFunctionsValues() == CCalculator::Values{
		{ "func1", 40.f },
		{ "func2", 40.f } });
}

TEST_CASE("Save func with addition tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1", 40.f);
	calculator.SaveVar("var2");
	calculator.SaveFunc("func1", "var1", CFunction::Operation::Add, "var2");

	CHECK(calculator.GetValue("func1") == nullopt);

	calculator.SaveVar("var2", 10.f);

	CHECK(calculator.GetValue("func1") == 50.f);

	try
	{
		calculator.SaveFunc("func2", "nonexistentName", CFunction::Operation::Add, "var2");
		CHECK(false);
	}
	catch (const runtime_error &)
	{
		CHECK(true);
	}
	try
	{
		calculator.SaveFunc("func2", "var1", CFunction::Operation::Add, "nonexistentName");
		CHECK(false);
	}
	catch (const runtime_error &)
	{
		CHECK(true);
	}
}

TEST_CASE("Save func with subtraction tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1", 40.f);
	calculator.SaveVar("var2", 10.f);
	calculator.SaveFunc("func1", "var1", CFunction::Operation::Sub, "var2");

	CHECK(calculator.GetValue("func1") == 30.f);
}

TEST_CASE("Save func with multiplication tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1", 40.f);
	calculator.SaveVar("var2", 10.f);
	calculator.SaveFunc("func1", "var1", CFunction::Operation::Mul, "var2");

	CHECK(calculator.GetValue("func1") == 400.f);
}

TEST_CASE("Save func with division tests")
{
	CCalculator calculator;
	calculator.SaveVar("var1", 40.f);
	calculator.SaveVar("var2", 10.f);
	calculator.SaveFunc("func1", "var1", CFunction::Operation::Div, "var2");

	CHECK(calculator.GetValue("func1") == 4.f);

	calculator.SaveVar("var2", 0.f);

	try
	{
		calculator.GetValue("func6");
		CHECK(false);
	}
	catch (const runtime_error &)
	{
		CHECK(true);
	}
}

TEST_CASE("50-th value of the Fibonacci numbers tests")
{
	CCalculator calculator;
	calculator.SaveVar("v0", 0.f);
	calculator.SaveVar("v1", 1.f);
	calculator.SaveFunc("fib0", "v0");
	calculator.SaveFunc("fib1", "v1");
	calculator.SaveFunc("fib2", "fib1", CFunction::Operation::Add, "fib0");
	calculator.SaveFunc("fib3", "fib2", CFunction::Operation::Add, "fib1");
	calculator.SaveFunc("fib4", "fib3", CFunction::Operation::Add, "fib2");
	calculator.SaveFunc("fib5", "fib4", CFunction::Operation::Add, "fib3");
	calculator.SaveFunc("fib6", "fib5", CFunction::Operation::Add, "fib4");
	calculator.SaveFunc("fib7", "fib6", CFunction::Operation::Add, "fib5");
	calculator.SaveFunc("fib8", "fib7", CFunction::Operation::Add, "fib6");
	calculator.SaveFunc("fib9", "fib8", CFunction::Operation::Add, "fib7");
	calculator.SaveFunc("fib10", "fib9", CFunction::Operation::Add, "fib8");
	calculator.SaveFunc("fib11", "fib10", CFunction::Operation::Add, "fib9");
	calculator.SaveFunc("fib12", "fib11", CFunction::Operation::Add, "fib10");
	calculator.SaveFunc("fib13", "fib12", CFunction::Operation::Add, "fib11");
	calculator.SaveFunc("fib14", "fib13", CFunction::Operation::Add, "fib12");
	calculator.SaveFunc("fib15", "fib14", CFunction::Operation::Add, "fib13");
	calculator.SaveFunc("fib16", "fib15", CFunction::Operation::Add, "fib14");
	calculator.SaveFunc("fib17", "fib16", CFunction::Operation::Add, "fib15");
	calculator.SaveFunc("fib18", "fib17", CFunction::Operation::Add, "fib16");
	calculator.SaveFunc("fib19", "fib18", CFunction::Operation::Add, "fib17");
	calculator.SaveFunc("fib20", "fib19", CFunction::Operation::Add, "fib18");
	calculator.SaveFunc("fib21", "fib20", CFunction::Operation::Add, "fib19");
	calculator.SaveFunc("fib22", "fib21", CFunction::Operation::Add, "fib20");
	calculator.SaveFunc("fib23", "fib22", CFunction::Operation::Add, "fib21");
	calculator.SaveFunc("fib24", "fib23", CFunction::Operation::Add, "fib22");
	calculator.SaveFunc("fib25", "fib24", CFunction::Operation::Add, "fib23");
	calculator.SaveFunc("fib26", "fib25", CFunction::Operation::Add, "fib24");
	calculator.SaveFunc("fib27", "fib26", CFunction::Operation::Add, "fib25");
	calculator.SaveFunc("fib28", "fib27", CFunction::Operation::Add, "fib26");
	calculator.SaveFunc("fib29", "fib28", CFunction::Operation::Add, "fib27");
	calculator.SaveFunc("fib30", "fib29", CFunction::Operation::Add, "fib28");
	calculator.SaveFunc("fib31", "fib30", CFunction::Operation::Add, "fib29");
	calculator.SaveFunc("fib32", "fib31", CFunction::Operation::Add, "fib30");
	calculator.SaveFunc("fib33", "fib32", CFunction::Operation::Add, "fib31");
	calculator.SaveFunc("fib34", "fib33", CFunction::Operation::Add, "fib32");
	calculator.SaveFunc("fib35", "fib34", CFunction::Operation::Add, "fib33");
	calculator.SaveFunc("fib36", "fib35", CFunction::Operation::Add, "fib34");
	calculator.SaveFunc("fib37", "fib36", CFunction::Operation::Add, "fib35");
	calculator.SaveFunc("fib38", "fib37", CFunction::Operation::Add, "fib36");
	calculator.SaveFunc("fib39", "fib38", CFunction::Operation::Add, "fib37");
	calculator.SaveFunc("fib40", "fib39", CFunction::Operation::Add, "fib38");
	calculator.SaveFunc("fib41", "fib40", CFunction::Operation::Add, "fib39");
	calculator.SaveFunc("fib42", "fib41", CFunction::Operation::Add, "fib40");
	calculator.SaveFunc("fib43", "fib42", CFunction::Operation::Add, "fib41");
	calculator.SaveFunc("fib44", "fib43", CFunction::Operation::Add, "fib42");
	calculator.SaveFunc("fib45", "fib44", CFunction::Operation::Add, "fib43");
	calculator.SaveFunc("fib46", "fib45", CFunction::Operation::Add, "fib44");
	calculator.SaveFunc("fib47", "fib46", CFunction::Operation::Add, "fib45");
	calculator.SaveFunc("fib48", "fib47", CFunction::Operation::Add, "fib46");
	calculator.SaveFunc("fib49", "fib48", CFunction::Operation::Add, "fib47");
	calculator.SaveFunc("fib50", "fib49", CFunction::Operation::Add, "fib48");
	CHECK((long long)calculator.GetValue("fib50").value() == 12586269025);
	calculator.SaveVar("v0", 1.f);
	CHECK((long long)calculator.GetValue("fib50").value() == 20365011074);
}