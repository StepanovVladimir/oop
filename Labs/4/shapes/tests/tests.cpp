#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../shapes/LineSegment.h"
#include "../shapes/Triangle.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"

using namespace std;

TEST_CASE("Point tests")
{
	CPoint point(1.0, 3.0);
	CHECK(point.GetX() == 1.0);
	CHECK(point.GetY() == 3.0);
}

TEST_CASE("Line segment tests")
{
	CPoint point1(1.0, 1.0);
	CPoint point2(5.0, 1.0);
	CLineSegment lineSegment(point1, point2, 0xff0000);

	CHECK(lineSegment.GetArea() == 0.0);
	CHECK(lineSegment.GetPerimeter() == 4.0);
	CHECK(lineSegment.GetOutlineColor() == 0xff0000);

	CHECK(lineSegment.GetStartPoint().GetX() == point1.GetX());
	CHECK(lineSegment.GetStartPoint().GetY() == point1.GetY());
	CHECK(lineSegment.GetEndPoint().GetX() == point2.GetX());
	CHECK(lineSegment.GetEndPoint().GetY() == point2.GetY());
}

TEST_CASE("Line segment of zero length tests")
{
	CPoint point1(1.0, 1.0);
	CPoint point2(1.0, 1.0);
	CLineSegment lineSegment(point1, point2, 0xff0000);

	CHECK(lineSegment.GetPerimeter() == 0.0);
}

TEST_CASE("Triangle tests")
{
	CPoint point1(0.0, 0.0);
	CPoint point2(3.0, 0.0);
	CPoint point3(0.0, 4.0);
	CTriangle triangle(point1, point2, point3, 0xff0000, 0x10ff00);

	CHECK(triangle.GetArea() == 6.0);
	CHECK(triangle.GetPerimeter() == 12.0);
	CHECK(triangle.GetOutlineColor() == 0xff0000);
	CHECK(triangle.GetFillColor() == 0x10ff00);

	CHECK(triangle.GetVertex1().GetX() == point1.GetX());
	CHECK(triangle.GetVertex1().GetY() == point1.GetY());
	CHECK(triangle.GetVertex2().GetX() == point2.GetX());
	CHECK(triangle.GetVertex2().GetY() == point2.GetY());
	CHECK(triangle.GetVertex3().GetX() == point3.GetX());
	CHECK(triangle.GetVertex3().GetY() == point3.GetY());
}

TEST_CASE("Triangle with zero area tests")
{
	CPoint point1(0.0, 0.0);
	CPoint point2(0.0, 0.0);
	CPoint point3(0.0, 4.0);
	CTriangle triangle(point1, point2, point3, 0xff0000, 0x10ff00);

	CHECK(triangle.GetArea() == 0.0);
	CHECK(triangle.GetPerimeter() == 8.0);
}

TEST_CASE("Rectangle tests")
{
	CPoint point(1.0, 1.0);

	CHECK_THROWS_AS(CRectangle(point, -1.0, 1.0, 0xff0000, 0x10ff00), runtime_error);
	CHECK_THROWS_AS(CRectangle(point, 1.0, -1.0, 0xff0000, 0x10ff00), runtime_error);

	CRectangle rectangle(point, 6.0, 4.0, 0xff0000, 0x10ff00);

	CHECK(rectangle.GetArea() == 24.0);
	CHECK(rectangle.GetPerimeter() == 20.0);
	CHECK(rectangle.GetOutlineColor() == 0xff0000);
	CHECK(rectangle.GetFillColor() == 0x10ff00);

	CHECK(rectangle.GetLeftTop().GetX() == point.GetX());
	CHECK(rectangle.GetLeftTop().GetY() == point.GetY());
	CHECK(rectangle.GetRightBottom().GetX() == 7.0);
	CHECK(rectangle.GetRightBottom().GetY() == 5.0);
	CHECK(rectangle.GetWidth() == 6.0);
	CHECK(rectangle.GetHeight() == 4.0);
}

TEST_CASE("Rectangle with zero height tests")
{
	CPoint point(1.0, 1.0);
	CRectangle rectangle(point, 6.0, 0.0, 0xff0000, 0x10ff00);

	CHECK(rectangle.GetArea() == 0.0);
	CHECK(rectangle.GetPerimeter() == 12.0);
}

TEST_CASE("Circle tests")
{
	CPoint point(6.0, 6.0);

	CHECK_THROWS_AS(CCircle(point, -1.0, 0xff0000, 0x10ff00), runtime_error);

	CCircle circle(point, 4.0, 0xff0000, 0x10ff00);

	CHECK(to_string(circle.GetArea()) == to_string(50.24));
	CHECK(to_string(circle.GetPerimeter()) == to_string(25.12));
	CHECK(circle.GetOutlineColor() == 0xff0000);
	CHECK(circle.GetFillColor() == 0x10ff00);

	CHECK(circle.GetCenter().GetX() == point.GetX());
	CHECK(circle.GetCenter().GetY() == point.GetY());
	CHECK(circle.GetRadius() == 4.0);
}

TEST_CASE("Circle with zero radius tests")
{
	CPoint point(6.0, 6.0);
	CCircle circle(point, 0.0, 0xff0000, 0x10ff00);

	CHECK(circle.GetArea() == 0.0);
	CHECK(circle.GetPerimeter() == 0.0);
}