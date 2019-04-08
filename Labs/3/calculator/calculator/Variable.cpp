#include "pch.h"
#include "Variable.h"

using namespace std;

CVariable::CVariable(optional<double> value)
	: m_value(value)
{
}

void CVariable::SetValue(optional<double> value)
{
	m_value = value;
}

optional<double> CVariable::GetValue() const
{
	return m_value;
}