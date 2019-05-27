#pragma once

#include "ITaxi.h"
#include "CCarImpl.h"

class CTaxi : public CCarImpl<ITaxi, IPerson>
{
public:
	CTaxi(size_t placeCount, MakeOfTheCar makeOfTheCar);
};