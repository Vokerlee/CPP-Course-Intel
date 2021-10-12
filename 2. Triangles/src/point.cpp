#include "../include/point.hpp"
#include "../include/vector.hpp"
#include "../include/line.hpp"
#include "../include/plane.hpp"

using namespace geom;

Point::Point(double x_val, double y_val , double z_val) :
    x(x_val), y(y_val), z(z_val)
{}

Point::Point(const Plane& pl, const Line& l)
{
    Vector normal = pl.get_normal();
    Vector direction = l.vector;

    double scalar = scalar_product(normal, direction); // != 0, cuz it was checked in advance

    double d = (-1) *  scalar_product(normal, static_cast<Vector>(pl.point));
    double t = (-1) * (scalar_product(normal, static_cast<Vector>(l.point)) + d) / scalar;

    Vector multiplied = t * direction;

    x = l.point.x + multiplied.x;
    y = l.point.y + multiplied.y;
    z = l.point.z + multiplied.z;
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

Point::operator Vector() const
{
    return Vector(x, y, z);
}

namespace geom
{
    std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << "Point(" << p.x << ", " << p.y << ", " << p.z << ")";

        return out;
    }
}
