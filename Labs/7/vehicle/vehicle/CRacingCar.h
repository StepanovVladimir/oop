#pragma once

#include "IRacingCar.h"
#include "CCarImpl.h"

class CRacingCar : public CCarImpl<IRacingCar, IRacer>
{
public:
	CRacingCar(size_t placeCount, MakeOfTheCar makeOfTheCar);
};