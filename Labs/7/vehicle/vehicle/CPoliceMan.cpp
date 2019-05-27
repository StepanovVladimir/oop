#include "pch.h"
#include "CPoliceMan.h"

using namespace std;

CPoliceMan::CPoliceMan(const string &name, const string &departmentName)
	: CPersonImpl(name)
	, m_departmentName(departmentName)
{
}

string CPoliceMan::GetDepartmentName() const
{
	return m_departmentName;
}