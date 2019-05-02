#include "pch.h"
#include "Sportsman.h"

bool LessByHeight(Sportsman sportsman1, Sportsman sportsman2)
{
	return sportsman1.height < sportsman2.height;
}

bool LessByWeight(Sportsman sportsman1, Sportsman sportsman2)
{
	return sportsman1.weight < sportsman2.weight;
}