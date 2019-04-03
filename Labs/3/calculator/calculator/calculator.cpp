#include "pch.h"
#include <iostream>
#include "Storage.h"
#include <sstream>

using namespace std;

void CheckCorrectOfIdentifier(const string &identifierName)
{
	if (identifierName == "")
	{
		throw string("Invalid input string");
	}

	char ch = identifierName[0];
	if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z') && ch != '_')
	{
		throw string("Invalid identifier name");
	}

	for (size_t i = 1; i < identifierName.size(); i++)
	{
		ch = identifierName[i];
		if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z') && (ch < '0' || ch > '9') && ch != '_')
		{
			throw string("Invalid identifier name");
		}
	}
}

void CheckEndOfLine(istream &inStrm)
{
	char ch;
	while (inStrm.get(ch))
	{
		if (ch != ' ')
		{
			throw string("Invalid input string");
		}
	}
}

void SaveUndefinedVar(istream &inStrm)
{
	string varName;
	inStrm >> varName;

	CheckCorrectOfIdentifier(varName);
	CheckEndOfLine(inStrm);

	CStorage::SaveVar(varName);
}

string GetIdentifierName(istream &inStrm)
{
	char ch;
	while (inStrm.get(ch))
	{
		if (ch != ' ')
		{
			break;
		}
	}

	if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z') && ch != '_')
	{
		throw string("Invalid identifier name");
	}

	string identifierName;
	identifierName += ch;

	while (inStrm.get(ch))
	{
		if (ch == ' ' || ch == '=')
		{
			break;
		}
		if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z') && (ch < '0' || ch > '9') && ch != '_')
		{
			throw string("Invalid identifier name");
		}
		identifierName += ch;
	}

	if (inStrm.eof())
	{
		throw string("Invalid input string");
	}

	if (ch == ' ')
	{
		inStrm >> ch;
		if (ch != '=')
		{
			throw string("Invalid input string");
		}
	}
	return identifierName;
}

void SaveDefinedVar(istream &inStrm)
{
	string varName = GetIdentifierName(inStrm);

	string str;
	float f;
	inStrm >> str;
	istringstream strm(str);
	strm >> f;
	if (strm)
	{
		if (!strm.eof())
		{
			throw string("Invalid identifier name");
		}
		CheckEndOfLine(inStrm);
		CStorage::SaveVar(varName, f);
	}
	else
	{
		CheckCorrectOfIdentifier(str);
		CheckEndOfLine(inStrm);
		CStorage::SaveVar(varName, str);
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

void SaveFunc(istream &inStrm)
{
	string funcName = GetIdentifierName(inStrm);
	char ch;
	while (inStrm.get(ch))
	{
		if (ch != ' ')
		{
			break;
		}
	}

	if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z') && ch != '_')
	{
		throw string("Invalid identifier name");
	}
	string arg1Name;
	arg1Name += ch;
	while (inStrm.get(ch))
	{
		if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
			break;
		}
		if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z') && (ch < '0' || ch > '9') && ch != '_')
		{
			throw string("Invalid identifier name");
		}
		arg1Name += ch;
	}

	if (ch == ' ')
	{
		inStrm >> ch;
		if (ch != ' ' && ch != '+' && ch != '-' && ch != '*' && ch != '/')
		{
			throw string("Invalid input string");
		}
	}

	if (inStrm.eof())
	{
		CStorage::SaveFunc(funcName, arg1Name);
	}
	else
	{
		CFunction::Operation operation = GetOperation(ch);
		string arg2Name;
		inStrm >> arg2Name;
		CheckCorrectOfIdentifier(arg2Name);
		CheckEndOfLine(inStrm);
		CStorage::SaveFunc(funcName, arg1Name, operation, arg2Name);
	}
}

void PrintValue(istream &inStrm)
{
	string identifierName;
	inStrm >> identifierName;
	CheckCorrectOfIdentifier(identifierName);
	CheckEndOfLine(inStrm);

	optional<float> value = CStorage::GetValue(identifierName);
	if (!value)
	{
		cout << "nan\n";
	}
	else
	{
		cout << value.value() << endl;
	}
}

void PrintVariables()
{
	CStorage::Values values = CStorage::GetVariablesValues();
	for (const auto value : values)
	{
		cout << value.first << ':';
		if (!value.second)
		{
			cout << "nan\n";
		}
		else
		{
			cout << value.second.value() << endl;
		}
	}
}

void PrintFunctions()
{
	CStorage::Values values = CStorage::GetFunctionsValues();
	for (const auto value : values)
	{
		cout << value.first << ':';
		if (!value.second)
		{
			cout << "nan\n";
		}
		else
		{
			cout << value.second.value() << endl;
		}
	}
}

int main()
{
	string inStr, command;
	while (getline(cin, inStr))
	{
		istringstream inStrm(inStr);
		inStrm >> command;
		if (command == "var")
		{
			try 
			{
				SaveUndefinedVar(inStrm);
			}
			catch (const string &err)
			{
				cout << err << endl;
			}
		}
		else if (command == "let")
		{
			try
			{
				SaveDefinedVar(inStrm);
			}
			catch (const string &err)
			{
				cout << err << endl;
			}
		}
		else if (command == "fn")
		{
			try
			{
				SaveFunc(inStrm);
			}
			catch (const string &err)
			{
				cout << err << endl;
			}
		}
		else if (command == "print")
		{
			try
			{
				PrintValue(inStrm);
			}
			catch (const string &err)
			{
				cout << err << endl;
			}
		}
		else if (command == "printvars")
		{
			PrintVariables();
		}
		else if (command == "printfns")
		{
			PrintFunctions();
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

	return 0;
}