#include "pch.h"
#include "Variable.h"

using namespace std;

CVariable::CVariable()
	:m_value(nullopt)
{
}

CVariable::CVariable(optional<float> value)
	:m_value(value)
{
}

void CVariable::SetValue(optional<float> value)
{
	m_value = value;
}

optional<float> CVariable::GetValue() const
{
	return m_value;
}