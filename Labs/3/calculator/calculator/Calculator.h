#pragma once

#include "Variable.h"
#include "Function.h"
#include <map>

class CCalculator
{
public:
	using Values = std::map<std::string, std::optional<double>>;

	void SaveVar(const std::string &name);
	void SaveVar(const std::string &name, double value);
	void SaveVar(const std::string &name, const std::string &identifier);

	void SaveFunc(const std::string &name, const std::string &argName);
	void SaveFunc(const std::string &name, const std::string &arg1Name, CFunction::Operation operation, const std::string &arg2Name);

	std::optional<double> GetValue(const std::string &name);

	Values GetVariablesValues() const;
	Values GetFunctionsValues();

private:
	enum struct IdentifierType
	{
		Var,
		Func
	};

	std::map<std::string, CVariable> m_variables;
	std::map<std::string, CFunction> m_functions;
	std::map<std::string, IdentifierType> m_types;

	IdentifierType GetType(const std::string &name) const;
	std::optional<double> GetFuncValue(CFunction &name);
};