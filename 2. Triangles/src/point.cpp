#include "../include/point.hpp"

using namespace geom;

Point::Point(double x_val, double y_val , double z_val) :
    x(x_val), y(y_val), z(z_val)
{}

Point::Point(const Point& source)
{
    x = source.x;
    y = source.y;
    z = source.z;
}

void Point::operator=(const Point& source)
{
    x = source.x;
    y = source.y;
    z = source.z;
}

Point Point::operator-() const
{
    return {-x, -y, -z};
}

Point Point::operator+(const Point& source) const
{
    return {source.x + x, source.y + y, source.z + z};
}

Point Point::operator-(const Point& source) const
{
    return {x - source.x, y - source.y, z - source.z};
}

bool Point::operator==(const Point& source) const
{
    return std::abs(x - source.x) < TOLERANCE &&
           std::abs(y - source.y) < TOLERANCE &&
           std::abs(z - source.z) < TOLERANCE;
}

namespace geom
{
    std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << "Point(" << p.x << ", " << p.y << ", " << p.z << ")";

        return out;
    }
}
