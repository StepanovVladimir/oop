#pragma once

#include <string>
#include <optional>

class CFunction
{
public:
	enum struct Operation
	{
		No,
		Add,
		Sub,
		Mul,
		Div
	};

	CFunction(const std::string &argName);
	CFunction(const std::string &arg1Name, Operation operation, const std::string &arg2Name);
	
	void SetValue(std::optional<double> value);
	void DropValue();

	std::string GetArg1Name() const;
	std::string GetArg2Name() const;
	Operation GetOperation() const;

	bool ValueHasCalculated() const;
	std::optional<double> GetValue() const;

private:
	std::string m_arg1Name;
	std::string m_arg2Name;
	Operation m_operation;

	bool m_valueHasCalculated;
	std::optional<double> m_value;
};