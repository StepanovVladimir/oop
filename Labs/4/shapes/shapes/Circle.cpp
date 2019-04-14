#include "pch.h"
#include "Circle.h"
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

const double CCircle::PI = 3.14;

CCircle::CCircle(const CPoint &center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	if (radius < 0)
	{
		throw runtime_error("Radius cannot be negative");
	}
}

double CCircle::GetArea() const
{
	return PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return 2 * PI * m_radius;
}

string CCircle::ToString() const
{
	stringstream strm;
	strm << "Circle:\n  area: " << fixed << setprecision(2) << GetArea() << endl;
	strm << "  perimeter: " << fixed << setprecision(2) << GetPerimeter() << endl;
	strm << "  outline color: " << hex << m_outlineColor << endl;
	strm << "  fill color: " << hex << m_fillColor << endl;
	strm << "  center: " << fixed << setprecision(2) << m_center.GetX() << ", ";
	strm << fixed << setprecision(2) << m_center.GetY() << endl;
	strm << "  radius: " << fixed << setprecision(2) << m_radius << endl;
	return strm.str();
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}