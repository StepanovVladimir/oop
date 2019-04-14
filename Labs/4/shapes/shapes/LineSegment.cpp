#include "pch.h"
#include "LineSegment.h"
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

CLineSegment::CLineSegment(const CPoint &startPoint, const CPoint &endPoint, uint32_t outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_startPoint.GetX() - m_endPoint.GetX(), 2) + pow(m_startPoint.GetY() - m_endPoint.GetY(), 2));
}

string CLineSegment::ToString() const
{
	stringstream strm;
	strm << "Line segment:\n  length: " << fixed << setprecision(2) << GetPerimeter() << endl;
	strm << "  color: " << hex << m_outlineColor << endl;
	strm << "  start point: " << fixed << setprecision(2) << m_startPoint.GetX() << ", ";
	strm << fixed << setprecision(2) << m_startPoint.GetY() << endl;
	strm << "  end point: " << fixed << setprecision(2) << m_endPoint.GetX() << ", ";
	strm << fixed << setprecision(2) << m_endPoint.GetY() << endl;
	return strm.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}