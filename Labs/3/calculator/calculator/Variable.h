#pragma once

#include <string>
#include <optional>

class CVariable
{
public:
	CVariable();
	CVariable(std::optional<float> value);

	void SetValue(std::optional<float> value);

	std::optional<float> GetValue() const;

private:
	std::optional<float> m_value;
};