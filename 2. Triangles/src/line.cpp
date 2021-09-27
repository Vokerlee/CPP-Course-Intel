#include "../include/line.hpp"

using namespace geom;

Line::Line(const Point& p,  const Vector& v) :
    point(p), vector(v)
{}

Line::Line(const Point& p1, const Point& p2) :
    point(p1), vector(p1, p2)
{}

Line::Line(const Line& line)
{
    point  = line.point;
    vector = line.vector;
}

void Line::operator=(const Line& line)
{
    point  = line.point;
    vector = line.vector;
}

bool Line::operator==(const Line& line) const
{
    return (line.point == point) && (line.vector == vector);
}

namespace geom
{
    std::ostream& operator<<(std::ostream& out, const Line& l)
    {
        out << "(" << l.vector << ", " << l.point << ")";

        return out;
    }
}