#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../rational/Rational.h"
#include <sstream>

using namespace std;

TEST_CASE("Constructor on positive arguments tests")
{
	CRational rational1;
	CHECK(rational1.GetNumerator() == 0);
	CHECK(rational1.GetDenominator() == 1);
	CHECK(rational1.ToDouble() == 0.0);
	CHECK(rational1.ToCompoundFraction() == pair<int, CRational>(0, 0));

	CRational rational2(6);
	CHECK(rational2.GetNumerator() == 6);
	CHECK(rational2.GetDenominator() == 1);
	CHECK(rational2.ToDouble() == 6.0);
	CHECK(rational2.ToCompoundFraction() == pair<int, CRational>(6, 0));

	CRational rational3(8, 16);
	CHECK(rational3.GetNumerator() == 1);
	CHECK(rational3.GetDenominator() == 2);
	CHECK(to_string(rational3.ToDouble()) == to_string(0.5));
	CHECK(rational3.ToCompoundFraction() == pair<int, CRational>(0, CRational(1, 2)));

	CRational rational4(12, 8);
	CHECK(rational4.GetNumerator() == 3);
	CHECK(rational4.GetDenominator() == 2);
	CHECK(to_string(rational4.ToDouble()) == to_string(1.5));
	CHECK(rational4.ToCompoundFraction() == pair<int, CRational>(1, CRational(1, 2)));

	CHECK_THROWS_AS(CRational(1, 0), invalid_argument);
}

TEST_CASE("Constructor on negative arguments tests")
{
	CRational rational1(-6);
	CHECK(rational1.GetNumerator() == -6);
	CHECK(rational1.GetDenominator() == 1);
	CHECK(rational1.ToDouble() == -6.0);
	CHECK(rational1.ToCompoundFraction() == pair<int, CRational>(-6, 0));

	CRational rational2(-12, 3);
	CHECK(rational2.GetNumerator() == -4);
	CHECK(rational2.GetDenominator() == 1);
	CHECK(rational2.ToDouble() == -4.0);
	CHECK(rational2.ToCompoundFraction() == pair<int, CRational>(-4, 0));

	CRational rational3(12, -8);
	CHECK(rational3.GetNumerator() == -3);
	CHECK(rational3.GetDenominator() == 2);
	CHECK(to_string(rational3.ToDouble()) == to_string(-1.5));
	CHECK(rational3.ToCompoundFraction() == pair<int, CRational>(-1, CRational(-1, 2)));

	CRational rational4(-12, -3);
	CHECK(rational4.GetNumerator() == 4);
	CHECK(rational4.GetDenominator() == 1);
	CHECK(rational4.ToDouble() == 4.0);
	CHECK(rational4.ToCompoundFraction() == pair<int, CRational>(4, 0));
}

TEST_CASE("Operators unary '+' and '-' tests")
{
	CRational rational1 = +CRational(3, 5);
	CHECK(rational1.GetNumerator() == 3);
	CHECK(rational1.GetDenominator() == 5);

	CRational rational2 = -CRational(3, 5);
	CHECK(rational2.GetNumerator() == -3);
	CHECK(rational2.GetDenominator() == 5);
}

TEST_CASE("Operator binary '+' tests")
{
	CRational rational1 = CRational(1, 2) + CRational(1, 6);
	CHECK(rational1.GetNumerator() == 2);
	CHECK(rational1.GetDenominator() == 3);

	CRational rational2 = CRational(1, 2) + 1;
	CHECK(rational2.GetNumerator() == 3);
	CHECK(rational2.GetDenominator() == 2);

	CRational rational3 = 1 + CRational(1, 2);
	CHECK(rational3.GetNumerator() == 3);
	CHECK(rational3.GetDenominator() == 2);
}

TEST_CASE("Operator binary '-' tests")
{
	CRational rational1 = CRational(1, 2) - CRational(1, 6);
	CHECK(rational1.GetNumerator() == 1);
	CHECK(rational1.GetDenominator() == 3);

	CRational rational2 = CRational(1, 2) - 1;
	CHECK(rational2.GetNumerator() == -1);
	CHECK(rational2.GetDenominator() == 2);

	CRational rational3 = 1 - CRational(1, 2);
	CHECK(rational3.GetNumerator() == 1);
	CHECK(rational3.GetDenominator() == 2);
}

TEST_CASE("Operator '+=' tests")
{
	CRational rational1(1, 2);
	rational1 += CRational(1, 6);
	CHECK(rational1.GetNumerator() == 2);
	CHECK(rational1.GetDenominator() == 3);

	CRational rational2(1, 2);
	rational2 += 1;
	CHECK(rational2.GetNumerator() == 3);
	CHECK(rational2.GetDenominator() == 2);
}

TEST_CASE("Operator '-=' tests")
{
	CRational rational1(1, 2);
	rational1 -= CRational(1, 6);
	CHECK(rational1.GetNumerator() == 1);
	CHECK(rational1.GetDenominator() == 3);

	CRational rational2(1, 2);
	rational2 -= 1;
	CHECK(rational2.GetNumerator() == -1);
	CHECK(rational2.GetDenominator() == 2);
}

TEST_CASE("Operator '*' tests")
{
	CRational rational1 = CRational(1, 2) * CRational(2, 3);
	CHECK(rational1.GetNumerator() == 1);
	CHECK(rational1.GetDenominator() == 3);

	CRational rational2 = CRational(1, 2) * 3;
	CHECK(rational2.GetNumerator() == 3);
	CHECK(rational2.GetDenominator() == 2);

	CRational rational3 = 7 * CRational(2, 3);
	CHECK(rational3.GetNumerator() == 14);
	CHECK(rational3.GetDenominator() == 3);
}

TEST_CASE("Operator '/' tests")
{
	CRational rational1 = CRational(1, 2) / CRational(2, 3);
	CHECK(rational1.GetNumerator() == 3);
	CHECK(rational1.GetDenominator() == 4);

	CRational rational2 = CRational(1, 2) / 5;
	CHECK(rational2.GetNumerator() == 1);
	CHECK(rational2.GetDenominator() == 10);

	CRational rational3 = 7 / CRational(2, 3);
	CHECK(rational3.GetNumerator() == 21);
	CHECK(rational3.GetDenominator() == 2);
}

TEST_CASE("Operator '*=' tests")
{
	CRational rational1(1, 2);
	rational1 *= CRational(2, 3);
	CHECK(rational1.GetNumerator() == 1);
	CHECK(rational1.GetDenominator() == 3);

	CRational rational2(1, 2);
	rational2 *= 3;
	CHECK(rational2.GetNumerator() == 3);
	CHECK(rational2.GetDenominator() == 2);
}

TEST_CASE("Operator '/=' tests")
{
	CRational rational1(1, 2);
	rational1 /= CRational(2, 3);
	CHECK(rational1.GetNumerator() == 3);
	CHECK(rational1.GetDenominator() == 4);

	CRational rational2(1, 2);
	rational2 /= 3;
	CHECK(rational2.GetNumerator() == 1);
	CHECK(rational2.GetDenominator() == 6);
}

TEST_CASE("Operator '==' tests")
{
	CHECK(CRational(1, 2) == CRational(1, 2));
	CHECK(!(CRational(1, 2) == CRational(2, 3)));

	CHECK(CRational(4, 1) == 4);
	CHECK(!(CRational(1, 2) == 7));
	
	CHECK(3 == CRational(3, 1));
	CHECK(!(3 == CRational(2, 3)));
}

TEST_CASE("Operators '!=' tests")
{
	CHECK(!(CRational(1, 2) != CRational(1, 2)));
	CHECK(!(CRational(1, 2) == CRational(2, 3)));

	CHECK(CRational(4, 1) == 4);
	CHECK(!(CRational(1, 2) == 7));

	CHECK(3 == CRational(3, 1));
	CHECK(!(3 == CRational(2, 3)));
}

TEST_CASE("Operator '<' tests")
{
	CHECK(CRational(1, 3) < CRational(1, 2));
	CHECK(!(CRational(1, 2) < CRational(1, 2)));
	CHECK(!(CRational(1, 2) < CRational(1, 3)));

	CHECK(CRational(1, 2) < 7);
	CHECK(!(CRational(2, 1) < 2));
	CHECK(!(CRational(2, 1) < 1));

	CHECK(2 < CRational(3, 1));
	CHECK(!(3 < CRational(3, 1)));
	CHECK(!(4 < CRational(3, 1)));
}

TEST_CASE("Operator '<=' tests")
{
	CHECK(CRational(1, 3) <= CRational(1, 2));
	CHECK(CRational(1, 2) <= CRational(1, 2));
	CHECK(!(CRational(1, 2) <= CRational(1, 3)));

	CHECK(CRational(1, 2) <= 7);
	CHECK(CRational(2, 1) <= 2);
	CHECK(!(CRational(2, 1) <= 1));

	CHECK(2 <= CRational(3, 1));
	CHECK(3 <= CRational(3, 1));
	CHECK(!(4 <= CRational(3, 1)));
}

TEST_CASE("Operator '>' tests")
{
	CHECK(CRational(1, 2) > CRational(1, 3));
	CHECK(!(CRational(1, 2) > CRational(1, 2)));
	CHECK(!(CRational(1, 3) > CRational(1, 2)));

	CHECK(CRational(3, 1) > 2);
	CHECK(!(CRational(3, 1) > 3));
	CHECK(!(CRational(3, 1) > 4));

	CHECK(7 > CRational(1, 2));
	CHECK(!(2 > CRational(2, 1)));
	CHECK(!(1 > CRational(2, 1)));
}

TEST_CASE("Operator '>=' tests")
{
	CHECK(CRational(1, 2) >= CRational(1, 3));
	CHECK(CRational(1, 2) >= CRational(1, 2));
	CHECK(!(CRational(1, 3) >= CRational(1, 2)));

	CHECK(CRational(3, 1) >= 2);
	CHECK(CRational(3, 1) >= 3);
	CHECK(!(CRational(3, 1) >= 4));

	CHECK(7 >= CRational(1, 2));
	CHECK(2 >= CRational(2, 1));
	CHECK(!(1 >= CRational(2, 1)));
}

TEST_CASE("Operator '<<' tests")
{
	ostringstream outStrm;
	CRational rational(7, 15);
	outStrm << rational;
	CHECK(outStrm.str() == "7/15");
}

TEST_CASE("Operator '>>' tests")
{
	istringstream inStrm1("7/15");
	CRational rational1;
	inStrm1 >> rational1;
	CHECK(rational1.GetNumerator() == 7);
	CHECK(rational1.GetDenominator() == 15);

	istringstream inStrm2("7abc");
	CRational rational2;
	inStrm2 >> rational2;
	CHECK(inStrm2.failbit);
	CHECK(rational2.GetNumerator() == 0);
	CHECK(rational2.GetDenominator() == 1);

	istringstream inStrm3("7/abc");
	CRational rational3;
	inStrm3 >> rational3;
	CHECK(inStrm3.failbit);
	CHECK(rational3.GetNumerator() == 0);
	CHECK(rational3.GetDenominator() == 1);
}