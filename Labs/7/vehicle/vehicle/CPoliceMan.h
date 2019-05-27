#pragma once

#include "IPoliceMan.h"
#include "CPersonImpl.h"

class CPoliceMan : public CPersonImpl<IPoliceMan>
{
public:
	CPoliceMan(const std::string &name, const std::string &departmentName);
	std::string GetDepartmentName() const override;

private:
	std::string m_departmentName;
};