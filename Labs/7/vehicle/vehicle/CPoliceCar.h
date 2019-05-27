#pragma once

#include "IPoliceCar.h"
#include "CCarImpl.h"

class CPoliceCar : public CCarImpl<IPoliceCar, IPoliceMan>
{
public:
	CPoliceCar(size_t placeCount, MakeOfTheCar makeOfTheCar);
};