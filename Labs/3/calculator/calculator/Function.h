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
	std::optional<float> GetValue() const;

private:
	std::string m_arg1Name;
	std::string m_arg2Name;
	Operation m_operation;
};