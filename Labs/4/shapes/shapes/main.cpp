#include "pch.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

unique_ptr<CLineSegment> CreateLineSegment(istream &inStrm)
{
	double x1, y1, x2, y2;
	uint32_t outlineColor;
	inStrm >> x1 >> y1 >> x2 >> y2 >> hex >> outlineColor;
	if (!inStrm)
	{
		throw runtime_error("Invalid input string");
	}
	char ch = ' ';
	inStrm >> ch;
	if (ch != ' ')
	{
		throw runtime_error("Invalid input string");
	}
	CPoint startPoint(x1, y1);
	CPoint endPoint(x2, y2);
	return make_unique<CLineSegment>(startPoint, endPoint, outlineColor);
}

unique_ptr<CTriangle> CreateTriangle(istream &inStrm)
{
	double x1, y1, x2, y2, x3, y3;
	uint32_t outlineColor, fillColor;
	inStrm >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> hex >> outlineColor >> fillColor;
	if (!inStrm)
	{
		throw runtime_error("Invalid input string");
	}
	char ch = ' ';
	inStrm >> ch;
	if (ch != ' ')
	{
		throw runtime_error("Invalid input string");
	}
	CPoint vertex1(x1, y1);
	CPoint vertex2(x2, y2);
	CPoint vertex3(x3, y3);
	return make_unique<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

unique_ptr<CRectangle> CreateRectangle(istream &inStrm)
{
	double x, y, width, height;
	uint32_t outlineColor, fillColor;
	inStrm >> x >> y >> width >> height >> hex >> outlineColor >> fillColor;
	if (!inStrm)
	{
		throw runtime_error("Invalid input string");
	}
	char ch = ' ';
	inStrm >> ch;
	if (ch != ' ')
	{
		throw runtime_error("Invalid input string");
	}
	CPoint leftTop(x, y);
	return make_unique<CRectangle>(leftTop, width, height, outlineColor, fillColor);
}

unique_ptr<CCircle> CreateCircle(istream &inStrm)
{
	double x, y, radius;
	uint32_t outlineColor, fillColor;
	inStrm >> x >> y >> radius >> hex >> outlineColor >> fillColor;
	if (!inStrm)
	{
		throw runtime_error("Invalid input string");
	}
	char ch = ' ';
	inStrm >> ch;
	if (ch != ' ')
	{
		throw runtime_error("Invalid input string");
	}
	CPoint center(x, y);
	return make_unique<CCircle>(center, radius, outlineColor, fillColor);
}

unique_ptr<IShape> CreateShape(const string &inStr)
{
	string name;
	istringstream inStrm(inStr);
	inStrm >> name;
	if (name == "lineSegment")
	{
		return CreateLineSegment(inStrm);
	}
	else if (name == "triangle")
	{
		return CreateTriangle(inStrm);
	}
	else if (name == "rectangle")
	{
		return CreateRectangle(inStrm);
	}
	else if (name == "circle")
	{
		return CreateCircle(inStrm);
	}
	else
	{
		throw runtime_error("Invalid input string");
	}
}

vector<unique_ptr<IShape>> CreateShapes()
{
	vector<unique_ptr<IShape>> shapes;
	string inStr;
	while (getline(cin, inStr))
	{
		try
		{
			shapes.push_back(CreateShape(inStr));
		}
		catch (const runtime_error &err)
		{
			cout << err.what() << endl;
		}
	}
	return shapes;
}

void PrintShapeWhithLargestArea(const vector<unique_ptr<IShape>> &shapes)
{
	if (shapes.size() > 0)
	{
		size_t index = 0;
		double largestArea = shapes[index]->GetArea();
		for (size_t i = 1; i < shapes.size(); i++)
		{
			double area = shapes[i]->GetArea();
			if (area > largestArea)
			{
				largestArea = area;
				index = i;
			}
		}
		cout << "Shape whith largest area:\n" << shapes[index]->ToString() << endl;
	}
}

void PrintShapeWhithSmallestPerimeter(const vector<unique_ptr<IShape>> &shapes)
{
	if (shapes.size() > 0)
	{
		size_t index = 0;
		double smallestPerimeter = shapes[index]->GetPerimeter();
		for (size_t i = 1; i < shapes.size(); i++)
		{
			double perimeter = shapes[i]->GetPerimeter();
			if (perimeter < smallestPerimeter)
			{
				smallestPerimeter = perimeter;
				index = i;
			}
		}
		cout << "Shape whith smallest perimeter:\n" << shapes[index]->ToString() << endl;
	}
}

int main()
{
	vector<unique_ptr<IShape>> shapes = CreateShapes();
	PrintShapeWhithLargestArea(shapes);
	PrintShapeWhithSmallestPerimeter(shapes);
	return 0;
}