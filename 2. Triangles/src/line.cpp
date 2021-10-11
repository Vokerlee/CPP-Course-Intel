#include "../include/line.hpp"
#include "../include/plane.hpp"
#include "../include/vector.hpp"

using namespace geom;

Line::Line(const Point& p, const Vector& v) :
    point(p), vector(v)
{}

Line::Line(const Point& p1, const Point& p2) :
    point(p1), vector(p1, p2)
{}

Line::Line(const Plane& p1, const Plane& p2)
{
    Vector n1 = p1.get_normal();
    Vector n2 = p2.get_normal();

    Vector direction = vector_product(n1, n2);

    if (direction == Vector())
    {
        point  = Point();
        vector = Vector();
    }
    else
    {
        n1.normalize();
        n2.normalize();

        double n1_n2_prod = scalar_product(n1, n2);
        double n1_prod    = scalar_product(n1, n1);
        double n2_prod    = scalar_product(n2, n2);

        double s1 = scalar_product(n1, static_cast<Vector>(p1.point));
        double s2 = scalar_product(n2, static_cast<Vector>(p2.point));

        double a = (s2 * n1_n2_prod - s1 * n2_prod) / (n1_n2_prod * n1_n2_prod - n1_prod * n2_prod);
        double b = (s1 * n1_n2_prod - s2 * n2_prod) / (n1_n2_prod * n1_n2_prod - n1_prod * n2_prod);

        Vector temp(a * n1 + b * n2);

        point = Point(temp.x, temp.y, temp.z);
    }
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