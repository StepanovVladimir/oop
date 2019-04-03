#pragma once

#include "Variable.h"
#include "Function.h"
#include <map>

class CStorage
{
public:
	using Values = std::map<std::string, std::optional<float>>;

	static void SaveVar(const std::string &name);
	static void SaveVar(const std::string &name, float value);
	static void SaveVar(const std::string &name, const std::string &identifier);

	static void SaveFunc(const std::string &name, const std::string &argName);
	static void SaveFunc(const std::string &name, const std::string &arg1Name, CFunction::Operation operation, const std::string &arg2Name);
	
	static std::optional<float> GetValue(const std::string &name);
	
	static Values GetVariablesValues();
	static Values GetFunctionsValues();

private:
	enum struct IdentifierType
	{
		Var,
		Func
	};

	static std::map<std::string, CVariable> m_variables;
	static std::map<std::string, CFunction> m_functions;
	static std::map<std::string, IdentifierType> m_types;

	static std::optional<float> GetVarValue(const std::string &name);
	static std::optional<float> GetFuncValue(const std::string &name);
	static IdentifierType GetType(const std::string &name);
};