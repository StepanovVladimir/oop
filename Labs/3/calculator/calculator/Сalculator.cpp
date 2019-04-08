#include "pch.h"
#include "Calculator.h"

using namespace std;

void CCalculator::SaveVar(const string &name)
{
	auto iter = m_types.find(name);
	if (iter != m_types.end())
	{
		throw runtime_error("There is already a identifier with name: " + name);
	}

	m_variables[name] = CVariable();
	m_types[name] = IdentifierType::Var;
}

void CCalculator::SaveVar(const string &name, double value)
{
	auto iterFunc = m_functions.find(name);
	if (iterFunc != m_functions.end())
	{
		throw runtime_error("There is already a function with name: " + name);
	}

	auto iterVar = m_variables.find(name);
	if (iterVar == m_variables.end())
	{
		m_variables[name] = CVariable(value);
		m_types[name] = IdentifierType::Var;
	}
	else
	{
		iterVar->second.SetValue(value);
		for (auto &function : m_functions)
		{
			function.second.DropValue();
		}
	}
}

void CCalculator::SaveVar(const string &name, const std::string &identifier)
{
	auto iterFunc = m_functions.find(name);
	if (iterFunc != m_functions.end())
	{
		throw runtime_error("There is already a function with name: " + name);
	}

	auto iterVar = m_variables.find(name);
	if (iterVar == m_variables.end())
	{
		m_variables[name] = CVariable(GetValue(identifier));
		m_types[name] = IdentifierType::Var;
	}
	else
	{
		iterVar->second.SetValue(GetValue(identifier));
		for (auto &function : m_functions)
		{
			function.second.DropValue();
		}
	}
}

void CCalculator::SaveFunc(const string &name, const string &argName)
{
	auto iter = m_types.find(name);
	if (iter != m_types.end())
	{
		throw runtime_error("There is already a identifier with name: " + name);
	}

	auto iterArg = m_types.find(argName);
	if (iterArg == m_types.end())
	{
		throw runtime_error("There is no identifier with the name: " + argName);
	}

	m_functions.emplace(name, CFunction(argName));
	m_types[name] = IdentifierType::Func;
}

void CCalculator::SaveFunc(const string &name, const string &arg1Name, CFunction::Operation operation, const string &arg2Name)
{
	auto iter = m_types.find(name);
	if (iter != m_types.end())
	{
		throw runtime_error("There is already a identifier with name: " + name);
	}

	auto iterArg1 = m_types.find(arg1Name);
	if (iterArg1 == m_types.end())
	{
		throw runtime_error("There is no identifier with the name: " + arg1Name);
	}
	auto iterArg2 = m_types.find(arg2Name);
	if (iterArg2 == m_types.end())
	{
		throw runtime_error("There is no identifier with the name: " + arg2Name);
	}

	m_functions.emplace(name, CFunction(arg1Name, operation, arg2Name));
	m_types[name] = IdentifierType::Func;
}

optional<double> CCalculator::GetValue(const std::string &name)
{
	if (GetType(name) == IdentifierType::Var)
	{
		auto iter = m_variables.find(name);
		return iter->second.GetValue();
	}
	else
	{
		auto iter = m_functions.find(name);
		return GetFuncValue(iter->second);
	}
}

CCalculator::Values CCalculator::GetVariablesValues() const
{
	Values values;
	for (const auto &variable : m_variables)
	{
		values[variable.first] = variable.second.GetValue();
	}
	return values;
}

CCalculator::Values CCalculator::GetFunctionsValues()
{
	Values values;
	for (auto &function : m_functions)
	{
		values[function.first] = GetFuncValue(function.second);
	}
	return values;
}

CCalculator::IdentifierType CCalculator::GetType(const string &name) const
{
	auto iter = m_types.find(name);
	if (iter == m_types.end())
	{
		throw runtime_error("There is no identifier with the name: " + name);
	}
	return iter->second;
}

optional<double> CCalculator::GetFuncValue(CFunction &func)
{
	if (func.ValueHasCalculated())
	{
		return func.GetValue();
	}

	optional<double> arg1, arg2;
	if (func.GetOperation() == CFunction::Operation::No)
	{
		arg1 = GetValue(func.GetArg1Name());
		func.SetValue(arg1);
		return arg1;
	}
	else
	{
		arg1 = GetValue(func.GetArg1Name());
		arg2 = GetValue(func.GetArg2Name());
		if (!arg1 || !arg2)
		{
			func.SetValue(nullopt);
			return nullopt;
		}

		switch (func.GetOperation())
		{
		case CFunction::Operation::Add:
			func.SetValue(arg1.value() + arg2.value());
			return arg1.value() + arg2.value();

		case CFunction::Operation::Sub:
			func.SetValue(arg1.value() - arg2.value());
			return arg1.value() - arg2.value();

		case CFunction::Operation::Mul:
			func.SetValue(arg1.value() * arg2.value());
			return arg1.value() * arg2.value();

		case CFunction::Operation::Div:
			if (arg2.value() == 0)
			{
				throw runtime_error("Division by zero occurs");
			}
			func.SetValue(arg1.value() / arg2.value());
			return arg1.value() / arg2.value();

		default:
			return nullopt;
		}
	}
}
