#include "pch.h"
#include "Solver.h"
#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <iomanip>

using namespace std;

using Coefficients = array<double, 4>;

Coefficients GetCoefficientsOfEquationOf3Degree(const string &inStr)
{
	Coefficients coeffs;
	istringstream inStrm(inStr);
	inStrm >> coeffs[0] >> coeffs[1] >> coeffs[2] >> coeffs[3];
	if (!inStrm)
	{
		throw runtime_error("Invalid input string");
	}
	return coeffs;
}

void PrintEquationRoots(const EquationRoots3 &equationRoots)
{
	for (int i = 0; i < equationRoots.numRoots; i++)
	{
		cout << fixed << setprecision(3) << equationRoots.roots[i] << ' ';
	}
	cout << endl;
}

int main()
{
	string inStr;
	while (getline(cin, inStr))
	{
		try
		{
			Coefficients coeffs = GetCoefficientsOfEquationOf3Degree(inStr);
			EquationRoots3 equationRoots = Solve3(coeffs[0], coeffs[1], coeffs[2], coeffs[3]);
			PrintEquationRoots(equationRoots);
		}
		catch (const runtime_error &err)
		{
			cout << err.what() << endl;
		}
		catch (const invalid_argument &err)
		{
			cout << err.what() << endl;
		}
	}
	return 0;
}