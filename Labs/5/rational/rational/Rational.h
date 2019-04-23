#pragma once

#include <iostream>

class CRational
{
public:
	CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	CRational const operator+() const;
	CRational const operator-() const;

	CRational const friend operator+(const CRational &rational1, const CRational &rational2);
	CRational const friend operator-(const CRational &rational1, const CRational &rational2);

	CRational &operator+=(const CRational &rational);
	CRational &operator-=(const CRational &rational);

	CRational const friend operator*(const CRational &rational1, const CRational &rational2);
	CRational const friend operator/(const CRational &rational1, const CRational &rational2);

	CRational &operator*=(const CRational &rational);
	CRational &operator/=(const CRational &rational);

	bool friend operator==(const CRational &rational1, const CRational &rational2);
	bool friend operator!=(const CRational &rational1, const CRational &rational2);
	bool friend operator<(const CRational &rational1, const CRational &rational2);
	bool friend operator<=(const CRational &rational1, const CRational &rational2);
	bool friend operator>(const CRational &rational1, const CRational &rational2);
	bool friend operator>=(const CRational &rational1, const CRational &rational2);

	std::ostream friend &operator<<(std::ostream &outStrm, const CRational &rational);
	std::istream friend &operator>>(std::istream &inStrm, CRational &rational);

private:
	int m_numerator;
	int m_denominator;

	static int GetGCD(int i1, int i2);
	static int GetLCM(int i1, int i2);
};