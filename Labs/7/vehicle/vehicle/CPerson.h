#pragma once

#include "IPerson.h"
#include "CPersonImpl.h"

class CPerson : public CPersonImpl<IPerson>
{
public:
	CPerson(const std::string &name);
};