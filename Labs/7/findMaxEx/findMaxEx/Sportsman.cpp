#include "pch.h"
#include "Sportsman.h"

bool LessByHeight(const Sportsman &sportsman1, const Sportsman &sportsman2)
{
	return sportsman1.height < sportsman2.height;
}

bool LessByWeight(const Sportsman &sportsman1, const Sportsman &sportsman2)
{
	return sportsman1.weight < sportsman2.weight;
}