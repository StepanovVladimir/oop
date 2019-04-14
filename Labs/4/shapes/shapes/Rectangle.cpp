#include "pch.h"
#include "Rectangle.h"
#include <sstream>
#include <iomanip>

using namespace std;

CRectangle::CRectangle(const CPoint &leftTop, double width, double height,
	uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	if (width < 0 || height < 0)
	{
		throw runtime_error("Width and height cannot be negative");
	}
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

string CRectangle::ToString() const
{
	stringstream strm;
	strm << "Rectangle:\n  area: " << fixed << setprecision(2) << GetArea() << endl;
	strm << "  perimeter: " << fixed << setprecision(2) << GetPerimeter() << endl;
	strm << "  outline color: " << hex << m_outlineColor << endl;
	strm << "  fill color: " << hex << m_fillColor << endl;
	strm << "  left top vertex: " << fixed << setprecision(2) << m_leftTop.GetX() << ", ";
	strm << fixed << setprecision(2) << m_leftTop.GetY() << endl;
	strm << "  width: " << fixed << setprecision(2) << m_width << endl;
	strm << "  height: " << fixed << setprecision(2) << m_height << endl;
	return strm.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}