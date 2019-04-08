#include "pch.h"
#include "Function.h"
#include "Calculator.h"
#include <iostream>

using namespace std;

CFunction::CFunction(const string &argName)
	: m_arg1Name(argName),
	m_operation(Operation::No),
	m_valueHasCalculated(false)
{
}

CFunction::CFunction(const string &arg1Name, Operation operation, const string &arg2Name)
	: m_arg1Name(arg1Name),
	m_operation(operation),
	m_arg2Name(arg2Name),
	m_valueHasCalculated(false)
{
}

void CFunction::SetValue(optional<double> value)
{
	m_value = value;
	m_valueHasCalculated = true;
}

void CFunction::DropValue()
{
	m_valueHasCalculated = false;
}

string CFunction::GetArg1Name() const
{
	return m_arg1Name;
}

string CFunction::GetArg2Name() const
{
	return m_arg2Name;
}

CFunction::Operation CFunction::GetOperation() const
{
	return m_operation;
}

bool CFunction::ValueHasCalculated() const
{
	return m_valueHasCalculated;
}

optional<double> CFunction::GetValue() const
{
	return m_value;
}