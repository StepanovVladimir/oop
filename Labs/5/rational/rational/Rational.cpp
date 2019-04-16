#include "pch.h"
#include "Rational.h"
#include <algorithm>

using namespace std;

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw invalid_argument("The denominator cannot be zero");
	}
	int GCD = GetGCD(numerator, denominator);
	numerator /= GCD;
	denominator /= GCD;
	if (numerator >= 0 && denominator >= 0 || numerator <= 0 || denominator >= 0)
	{
		m_numerator = numerator;
		m_denominator = denominator;
	}
	else
	{
		m_numerator = -numerator;
		m_denominator = -denominator;
	}
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return double(m_numerator) / double(m_denominator);
}

pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integerPart = m_numerator / m_denominator;
	CRational fractionalPart(m_numerator % m_denominator, m_denominator);
	return pair<int, CRational>(integerPart, fractionalPart);
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const operator+(const CRational &rational1, const CRational &rational2)
{
	int LCM = CRational::GetLCM(rational1.GetDenominator(), rational2.GetDenominator());
	int numerator1 = rational1.GetNumerator() * (LCM / rational1.GetDenominator());
	int numerator2 = rational2.GetNumerator() * (LCM / rational2.GetDenominator());
	return CRational(numerator1 + numerator2, LCM);
}

CRational const operator-(const CRational &rational1, const CRational &rational2)
{
	int LCM = CRational::GetLCM(rational1.GetDenominator(), rational2.GetDenominator());
	int numerator1 = rational1.GetNumerator() * (LCM / rational1.GetDenominator());
	int numerator2 = rational2.GetNumerator() * (LCM / rational2.GetDenominator());
	return CRational(numerator1 - numerator2, LCM);
}

CRational &CRational::operator+=(const CRational &rational)
{
	*this = *this + rational;
	return *this;
}

CRational &CRational::operator-=(const CRational &rational)
{
	*this = *this - rational;
	return *this;
}

CRational const operator*(const CRational &rational1, const CRational &rational2)
{
	int numerator = rational1.GetNumerator() * rational2.GetNumerator();
	int denominator = rational1.GetDenominator() * rational2.GetDenominator();
	return CRational(numerator, denominator);
}

CRational const operator/(const CRational &rational1, const CRational &rational2)
{
	int numerator = rational1.GetNumerator() * rational2.GetDenominator();
	int denominator = rational1.GetDenominator() * rational2.GetNumerator();
	return CRational(numerator, denominator);
}

CRational &CRational::operator*=(const CRational &rational)
{
	*this = *this * rational;
	return *this;
}

CRational &CRational::operator/=(const CRational &rational)
{
	*this = *this / rational;
	return *this;
}

bool operator==(const CRational &rational1, const CRational &rational2)
{
	bool numeratorsAreEqual = rational1.GetNumerator() == rational2.GetNumerator();
	bool denominatorsAreEqual = rational1.GetDenominator() == rational2.GetDenominator();
	return numeratorsAreEqual && denominatorsAreEqual;
}

bool operator!=(const CRational &rational1, const CRational &rational2)
{
	return !(rational1 == rational2);
}

bool operator<(const CRational &rational1, const CRational &rational2)
{
	return rational1.ToDouble() < rational2.ToDouble();
}

bool operator<=(const CRational &rational1, const CRational &rational2)
{
	return rational1 == rational2 || rational1 < rational2;
}

bool operator>(const CRational &rational1, const CRational &rational2)
{
	return rational1.ToDouble() > rational2.ToDouble();
}

bool operator>=(const CRational &rational1, const CRational &rational2)
{
	return rational1 == rational2 || rational1 > rational2;
}

ostream &operator<<(ostream &outStrm, const CRational &rational)
{
	outStrm << rational.GetNumerator() << '/' << rational.GetDenominator();
	return outStrm;
}

istream &operator>>(istream &inStrm, CRational &rational)
{
	int numerator, denominator;
	if (inStrm >> numerator && inStrm.get() == '/' && inStrm >> denominator)
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		inStrm.setstate(ios_base::failbit | inStrm.rdstate());
	}
	return inStrm;
}

int CRational::GetGCD(int i1, int i2)
{
	if (abs(i1) < abs(i2))
	{
		GetGCD(i2, i1);
	}

	if (i2 == 0)
	{
		return i1;
	}
	else
	{
		return GetGCD(i2, i1 % i2);
	}
}

int CRational::GetLCM(int i1, int i2)
{
	for (int i = max(i1, i2); ; i++)
	{
		if (i % i1 == 0 && i % i2 == 0)
		{
			return i;
		}
	}
	return 0;
}