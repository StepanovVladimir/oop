#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../solve3/Solver.h"
#include <sstream>
#include <iomanip>

using namespace std;

TEST_CASE("Zero coefficient at x^3")
{
	CHECK_THROWS_AS(Solve3(0, 1, 1, 1), invalid_argument);
}

TEST_CASE("Three equation roots tests")
{
	EquationRoots3 equationRoots = Solve3(2, -8, 8, -2);
	REQUIRE(equationRoots.numRoots == 3);

	ostringstream strm1, strm2, strm3;
	strm1 << fixed << setprecision(3) << equationRoots.roots[0];
	strm2 << fixed << setprecision(3) << equationRoots.roots[1];
	strm3 << fixed << setprecision(3) << equationRoots.roots[2];

	CHECK(strm1.str() == "0.382");
	CHECK(strm2.str() == "2.618");
	CHECK(strm3.str() == "1.000");
}

TEST_CASE("One equation root tests")
{
	EquationRoots3 equationRoots1 = Solve3(1, -4, 4, 1);
	REQUIRE(equationRoots1.numRoots == 1);
	ostringstream strm1;
	strm1 << fixed << setprecision(3) << equationRoots1.roots[0];
	CHECK(strm1.str() == "-0.206");

	EquationRoots3 equationRoots2 = Solve3(1, -2, 2, -1);
	REQUIRE(equationRoots2.numRoots == 1);
	ostringstream strm2;
	strm2 << fixed << setprecision(3) << equationRoots2.roots[0];
	CHECK(strm2.str() == "1.000");

	EquationRoots3 equationRoots3 = Solve3(1, -3, 3, 1);
	REQUIRE(equationRoots3.numRoots == 1);
	ostringstream strm3;
	strm3 << fixed << setprecision(3) << equationRoots3.roots[0];
	CHECK(strm3.str() == "-0.260");
}

TEST_CASE("Two equation roots tests")
{
	EquationRoots3 equationRoots = Solve3(1, -4, 4, 0);
	REQUIRE(equationRoots.numRoots == 2);

	ostringstream strm1, strm2;
	strm1 << fixed << setprecision(3) << equationRoots.roots[0];
	strm2 << fixed << setprecision(3) << equationRoots.roots[1];

	CHECK(strm1.str() == "0.000");
	CHECK(strm2.str() == "2.000");
}