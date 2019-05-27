#pragma once

#include "IRacer.h"
#include "CPersonImpl.h"

class CRacer : public CPersonImpl<IRacer>
{
public:
	CRacer(const std::string &name, size_t awardsCount);
	size_t GetAwardsCount() const override;

private:
	size_t m_awardsCount;
};

