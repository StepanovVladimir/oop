#pragma once

#include <string>
#include <optional>

class CVariable
{
public:
	CVariable(std::optional<double> value = std::nullopt);

	void SetValue(std::optional<double> value);

	std::optional<double> GetValue() const;

private:
	std::optional<double> m_value;
};