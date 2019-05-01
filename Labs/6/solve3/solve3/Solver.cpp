#include "pch.h"
#include "Solver.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

using namespace std;

double EPS = 0.00000001;

double GetCubeRoot(double d)
{
	return d >= 0 ? pow(d, 1.0 / 3.0) : -pow(-d, 1.0 / 3.0);
}

EquationRoots3 GetThreeEquationRoots(double b, double q, double r)
{
	double phi = acos(r / pow(q, 1.5)) / 3;
	EquationRoots3 equationRoots;
	equationRoots.numRoots = 3;
	equationRoots.roots[0] = -2 * sqrt(q) * cos(phi) - b / 3;
	equationRoots.roots[1] = -2 * sqrt(q) * cos(phi + 2 * M_PI / 3) - b / 3;
	equationRoots.roots[2] = -2 * sqrt(q) * cos(phi - 2 * M_PI / 3) - b / 3;
	return equationRoots;
}

EquationRoots3 GetOneEquationRoot(double b, double d, double q, double r)
{
	if (q > 0)
	{
		double phi = acosh(abs(r) / pow(q, 1.5)) / 3;
		EquationRoots3 equationRoots;
		equationRoots.numRoots = 1;
		equationRoots.roots[0] = (r >= 0 ? -2 : 2) * sqrt(q) * cosh(phi) - b / 3;
		return equationRoots;
	}
	else if (q < 0)
	{
		double phi = asinh(abs(r) / pow(abs(q), 1.5)) / 3;
		EquationRoots3 equationRoots;
		equationRoots.numRoots = 1;
		equationRoots.roots[0] = (r >= 0 ? -2 : 2) * sqrt(abs(q)) * sinh(phi) - b / 3;
		return equationRoots;
	}
	else
	{
		EquationRoots3 equationRoots;
		equationRoots.numRoots = 1;
		equationRoots.roots[0] = -GetCubeRoot(d - pow(b, 3) / 27) - b / 3;
		return equationRoots;
	}
}

EquationRoots3 GetTwoEquationRoots(double b, double r)
{
	EquationRoots3 equationRoots;
	equationRoots.numRoots = 2;
	equationRoots.roots[0] = -2 * GetCubeRoot(r) - b / 3;
	equationRoots.roots[1] = GetCubeRoot(r) - b / 3;
	return equationRoots;
}

EquationRoots3 Solve3(double a, double b, double c, double d)
{
	if (a == 0)
	{
		throw invalid_argument("The coefficient at x^3 cannot be zero");
	}

	b /= a;
	c /= a;
	d /= a;

	double q = (pow(b, 2) - 3 * c) / 9;
	double r = (2 * pow(b, 3) - 9 * b * c + 27 * d) / 54;
	double s = pow(q, 3) - pow(r, 2);

	if (abs(s) < EPS)
	{
		return GetTwoEquationRoots(b, r);
	}
	else if (s > 0)
	{
		return GetThreeEquationRoots(b, q, r);
	}
	else
	{
		return GetOneEquationRoot(b, d, q, r);
	}
}