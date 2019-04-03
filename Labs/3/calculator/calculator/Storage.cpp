#include "pch.h"
#include "Storage.h"

using namespace std;

std::map<std::string, CVariable> CStorage::m_variables;
std::map<std::string, CFunction> CStorage::m_functions;
std::map<std::string, CStorage::IdentifierType> CStorage::m_types;

void CStorage::SaveVar(const string &name)
{
	auto iter = m_types.find(name);
	if (iter != m_types.end())
	{
		throw string("There is already a identifier with name: " + name);
	}

	m_variables[name] = CVariable();
	m_types[name] = IdentifierType::Var;
}

void CStorage::SaveVar(const string &name, float value)
{
	auto iter = m_functions.find(name);
	if (iter != m_functions.end())
	{
		throw string("There is already a function with name: " + name);
	}

	m_variables[name] = CVariable(value);
	m_types[name] = IdentifierType::Var;
}

void CStorage::SaveVar(const string &name, const std::string &identifier)
{
	auto iter = m_functions.find(name);
	if (iter != m_functions.end())
	{
		throw string("There is already a function with name: " + name);
	}

	m_variables[name] = CVariable(GetValue(identifier));
	m_types[name] = IdentifierType::Var;
}

void CStorage::SaveFunc(const string &name, const string &argName)
{
	auto iter = m_types.find(name);
	if (iter != m_types.end())
	{
		throw string("There is already a identifier with name: " + name);
	}

	auto iterArg = m_types.find(argName);
	if (iterArg == m_types.end())
	{
		throw string("There is no identifier with the name: " + argName);
	}

	m_functions.insert(pair(name, CFunction(argName)));
	m_types[name] = IdentifierType::Func;
}

void CStorage::SaveFunc(const string &name, const string &arg1Name, CFunction::Operation operation, const string &arg2Name)
{
	auto iter = m_types.find(name);
	if (iter != m_types.end())
	{
		throw string("There is already a identifier with name: " + name);
	}

	auto iterArg1 = m_types.find(arg1Name);
	if (iterArg1 == m_types.end())
	{
		throw string("There is no identifier with the name: " + arg1Name);
	}
	auto iterArg2 = m_types.find(arg1Name);
	if (iterArg2 == m_types.end())
	{
		throw string("There is no identifier with the name: " + arg2Name);
	}

	m_functions.insert(pair(name, CFunction(arg1Name, operation, arg2Name)));
	m_types[name] = IdentifierType::Func;
}

optional<float> CStorage::GetValue(const std::string &name)
{
	if (GetType(name) == CStorage::IdentifierType::Var)
	{
		return GetVarValue(name);
	}
	else
	{
		return GetFuncValue(name);
	}
}

CStorage::Values CStorage::GetVariablesValues()
{
	Values values;
	for (const auto variable : m_variables)
	{
		values[variable.first] = variable.second.GetValue();
	}
	return values;
}

CStorage::Values CStorage::GetFunctionsValues()
{
	Values values;
	for (const auto function : m_functions)
	{
		values[function.first] = function.second.GetValue();
	}
	return values;
}

optional<float> CStorage::GetVarValue(const string &name)
{
	auto iter = m_variables.find(name);
	if (iter == m_variables.end())
	{
		throw string("There is no variable with the name: " + name);
	}
	return iter -> second.GetValue();
}

optional<float> CStorage::GetFuncValue(const std::string &name)
{
	auto iter = m_functions.find(name);
	if (iter == m_functions.end())
	{
		throw string("There is no function with the name: " + name);
	}
	return iter -> second.GetValue();
}

CStorage::IdentifierType CStorage::GetType(const std::string &name)
{
	auto iter = m_types.find(name);
	if (iter == m_types.end())
	{
		throw string("There is no identifier with the name: " + name);
	}
	return iter->second;
}