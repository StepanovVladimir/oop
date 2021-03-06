#include "pch.h"
#include "Calculator.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

bool FirstCharIsCorrect(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

bool CharIsCorrect(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_';
}

void CheckValidityOfIdentifier(const string &identifierName)
{
	if (identifierName == "")
	{
		throw runtime_error("Invalid input string");
	}

	if (!FirstCharIsCorrect(identifierName[0]))
	{
		throw runtime_error("Invalid identifier name");
	}

	for (size_t i = 1; i < identifierName.size(); i++)
	{
		if (!CharIsCorrect(identifierName[i]))
		{
			throw runtime_error("Invalid identifier name");
		}
	}
}

void SaveUndefinedVar(istream &inStrm, CCalculator &calculator)
{
	string varName;
	inStrm >> varName;

	CheckValidityOfIdentifier(varName);
	char ch = ' ';
	inStrm >> ch;
	if (ch != ' ')
	{
		throw runtime_error("Invalid input string");
	}

	calculator.SaveVar(varName);
}

void SaveDefinedVar(istream &inStrm, CCalculator &calculator)
{
	string varName;
	inStrm >> varName;
	CheckValidityOfIdentifier(varName);

	char ch = ' ';
	inStrm >> ch;
	if (ch != '=')
	{
		throw runtime_error("Invalid input string");
	}

	string identifier;
	double value;
	inStrm >> identifier;
	istringstream strm(identifier);
	strm >> value;
	if (strm)
	{
		if (!strm.eof())
		{
			throw runtime_error("Invalid identifier name");
		}

		ch = ' ';
		inStrm >> ch;
		if (ch != ' ')
		{
			throw runtime_error("Invalid input string");
		}

		calculator.SaveVar(varName, value);
	}
	else
	{
		CheckValidityOfIdentifier(identifier);

		ch = ' ';
		inStrm >> ch;
		if (ch != ' ')
		{
			throw runtime_error("Invalid input string");
		}

		calculator.SaveVar(varName, identifier);
	}
}

CFunction::Operation GetOperation(char ch)
{
	switch (ch)
	{
	case '+':
		return CFunction::Operation::Add;
	case '-':
		return CFunction::Operation::Sub;
	case '*':
		return CFunction::Operation::Mul;
	case '/':
		return CFunction::Operation::Div;
	default:
		return CFunction::Operation::No;
	}
}

void SaveFunc(istream &inStrm, CCalculator &calculator)
{
	string funcName;
	inStrm >> funcName;
	CheckValidityOfIdentifier(funcName);

	char ch = ' ';
	inStrm >> ch;
	if (ch != '=')
	{
		throw runtime_error("Invalid input string");
	}

	string arg1Name;
	inStrm >> arg1Name;
	CheckValidityOfIdentifier(arg1Name);

	ch = ' ';
	inStrm >> ch;
	if (ch != ' ' && ch != '+' && ch != '-' && ch != '*' && ch != '/')
	{
		throw runtime_error("Invalid input string");
	}

	if (ch == ' ')
	{
		calculator.SaveFunc(funcName, arg1Name);
	}
	else
	{
		CFunction::Operation operation = GetOperation(ch);
		string arg2Name;
		inStrm >> arg2Name;
		CheckValidityOfIdentifier(arg2Name);

		ch = ' ';
		inStrm >> ch;
		if (ch != ' ')
		{
			throw runtime_error("Invalid input string");
		}

		calculator.SaveFunc(funcName, arg1Name, operation, arg2Name);
	}
}

void PrintValue(istream &inStrm, CCalculator &calculator)
{
	string identifierName;
	inStrm >> identifierName;
	CheckValidityOfIdentifier(identifierName);

	char ch = ' ';
	inStrm >> ch;
	if (ch != ' ')
	{
		throw runtime_error("Invalid input string");
	}

	optional<double> value = calculator.GetValue(identifierName);
	if (!value)
	{
		cout << "nan\n";
	}
	else
	{
		ostringstream strm;
		strm << fixed << setprecision(2) << value.value();
		cout << strm.str() << endl;
	}
}

void PrintVariables(const CCalculator &calculator)
{
	CCalculator::Values values = calculator.GetVariablesValues();
	for (const auto &value : values)
	{
		cout << value.first << ':';
		if (!value.second)
		{
			cout << "nan\n";
		}
		else
		{
			ostringstream strm;
			strm << fixed << setprecision(2) << value.second.value();
			cout << strm.str() << endl;
		}
	}
}

void PrintFunctions(CCalculator &calculator)
{
	CCalculator::Values values = calculator.GetFunctionsValues();
	for (const auto &value : values)
	{
		cout << value.first << ':';
		if (!value.second)
		{
			cout << "nan\n";
		}
		else
		{
			ostringstream strm;
			strm << fixed << setprecision(2) << value.second.value();
			cout << strm.str() << endl;
		}
	}
}

int main()
{
	CCalculator calculator;
	string inStr;
	while (getline(cin, inStr))
	{
		try
		{
			string command;
			istringstream inStrm(inStr);
			inStrm >> command;
			if (command == "var")
			{
				SaveUndefinedVar(inStrm, calculator);
			}
			else if (command == "let")
			{
				SaveDefinedVar(inStrm, calculator);
			}
			else if (command == "fn")
			{
				SaveFunc(inStrm, calculator);
			}
			else if (command == "print")
			{
				PrintValue(inStrm, calculator);
			}
			else if (command == "printvars")
			{
				PrintVariables(calculator);
			}
			else if (command == "printfns")
			{
				PrintFunctions(calculator);
			}
			else if (command == "exit")
			{
				break;
			}
			else
			{
				cout << "Invalid input string" << endl;
			}
		}
		catch (const runtime_error &err)
		{
			cout << err.what() << endl;
		}
	}
	return 0;
}