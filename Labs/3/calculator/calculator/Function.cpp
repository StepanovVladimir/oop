#include "pch.h"
#include "Function.h"
#include "Storage.h"
#include <iostream>

using namespace std;

CFunction::CFunction(const string &argName)
	:m_arg1Name(argName),
	m_operation(Operation::No)
{
}

CFunction::CFunction(const string &arg1Name, Operation operation, const string &arg2Name)
	:m_arg1Name(arg1Name),
	m_operation(operation),
	m_arg2Name(arg2Name)
{
}

optional<float> CFunction::GetValue() const
{
	optional<float> arg1, arg2;
	switch (m_operation)
	{
	case Operation::No:
		return CStorage::GetValue(m_arg1Name);

	case Operation::Add:
		arg1 = CStorage::GetValue(m_arg1Name);
		arg2 = CStorage::GetValue(m_arg2Name);
		if (!arg1 || !arg2)
		{
			
			return nullopt;
		}
		return arg1.value() + arg2.value();

	case Operation::Sub:
		arg1 = CStorage::GetValue(m_arg1Name);
		arg2 = CStorage::GetValue(m_arg2Name);
		if (!arg1 || !arg2)
		{
			return nullopt;
		}
		return arg1.value() - arg2.value();

	case Operation::Mul:
		arg1 = CStorage::GetValue(m_arg1Name);
		arg2 = CStorage::GetValue(m_arg2Name);
		if (!arg1 || !arg2)
		{
			return nullopt;
		}
		return arg1.value() * arg2.value();

	case Operation::Div:
		arg1 = CStorage::GetValue(m_arg1Name);
		arg2 = CStorage::GetValue(m_arg2Name);
		if (!arg1 || !arg2)
		{
			return nullopt;
		}
		if (arg2.value() == 0)
		{
			throw string("Division by zero occurs");
		}
		return arg1.value() / arg2.value();

	default:
		return nullopt;
	}
}