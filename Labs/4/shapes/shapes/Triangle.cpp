#include "pch.h"
#include "Triangle.h"
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

CTriangle::CTriangle(const CPoint &vertex1, const CPoint &vertex2, const CPoint &vertex3,
	uint32_t outlineColor, uint32_t fillColor)
	: m_v1(vertex1)
	, m_v2(vertex2)
	, m_v3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
	return abs((m_v2.GetX() - m_v1.GetX()) * (m_v3.GetY() - m_v1.GetY()) - (m_v3.GetX() - m_v1.GetX()) * (m_v2.GetY() - m_v1.GetY())) / 2;
}

double CTriangle::GetPerimeter() const
{
	double length1 = sqrt(pow(m_v2.GetX() - m_v1.GetX(), 2) + pow(m_v2.GetY() - m_v1.GetY(), 2));
	double length2 = sqrt(pow(m_v3.GetX() - m_v2.GetX(), 2) + pow(m_v3.GetY() - m_v2.GetY(), 2));
	double length3 = sqrt(pow(m_v1.GetX() - m_v3.GetX(), 2) + pow(m_v1.GetY() - m_v3.GetY(), 2));
	return length1 + length2 + length3;
}

string CTriangle::ToString() const
{
	stringstream strm;
	strm << "Triangle:\n  area: " << fixed << setprecision(2) << GetArea() << endl;
	strm << "  perimeter: " << fixed << setprecision(2) << GetPerimeter() << endl;
	strm << "  outline color: " << hex << m_outlineColor << endl;
	strm << "  fill color: " << hex << m_fillColor << endl;
	strm << "  vertex 1: " << fixed << setprecision(2) << m_v1.GetX() << ", ";
	strm << fixed << setprecision(2) << m_v1.GetY() << endl;
	strm << "  vertex 2: " << fixed << setprecision(2) << m_v2.GetX() << ", ";
	strm << fixed << setprecision(2) << m_v2.GetY() << endl;
	strm << "  vertex 3: " << fixed << setprecision(2) << m_v3.GetX() << ", ";
	strm << fixed << setprecision(2) << m_v3.GetY() << endl;
	return strm.str();
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_v1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_v2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_v3;
}