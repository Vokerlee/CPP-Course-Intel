#include "../include/point.hpp"
#include "../include/vector.hpp"
#include "../include/line.hpp"
#include "../include/triangle.hpp"

using namespace geom;

Triangle::Triangle(const Point& p, const Vector& v1, const Vector& v2) :
    point1(p),
    point2(p.x + v1.x, p.y + v1.y, p.z + v1.z),
    point3(p.x + v2.x, p.y + v2.y, p.z + v2.z)
{}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) :
    point1(p1),
    point2(p2),
    point3(p3)
{}

bool Triangle::operator==(const Triangle& tr) const
{
    return (tr.point1 == point1) && (tr.point2 == point2) && (tr.point3 == point3);
}