#pragma once

#include "SolidShape.h"
#include "Point.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint &vertex1, const CPoint &vertex2, const CPoint &vertex3,
		uint32_t outlineColor, uint32_t fillColor);
	
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint m_v1;
	CPoint m_v2;
	CPoint m_v3;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};