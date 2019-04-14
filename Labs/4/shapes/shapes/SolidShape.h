#pragma once

#include "Shape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape() {};
	virtual uint32_t GetFillColor() const = 0;
};