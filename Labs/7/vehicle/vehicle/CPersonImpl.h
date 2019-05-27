#pragma once

#include <string>

template<typename Base>
class CPersonImpl : public Base
{
public:
	CPersonImpl(const std::string &name)
		: m_name(name)
	{
	}

	std::string GetName() const override
	{
		return m_name;
	}

private:
	std::string m_name;
};