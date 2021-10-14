#include "../include/line.hpp"
#include "../include/plane.hpp"
#include "../include/vector.hpp"

namespace geom
{
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
        vector = direction;

        if (direction == Vector())
        {
            point  = Point();
            vector = Vector();
        }
        else
        {
            n1.normalize();
            n2.normalize();

            double cos_n1_n2 = scalar_product(n1, n2);

            double s1 = scalar_product(n1, static_cast<Vector>(p1.point));
            double s2 = scalar_product(n2, static_cast<Vector>(p2.point));

            double a = (s2 * cos_n1_n2 - s1) / (cos_n1_n2 * cos_n1_n2 - 1);
            double b = (s1 * cos_n1_n2 - s2) / (cos_n1_n2 * cos_n1_n2 - 1);

            Vector temp(a * n1 + b * n2);

            point = Point(temp.x, temp.y, temp.z);
        }
    }

    bool Line::operator==(const Line& line) const
    {
        Vector diff = static_cast<Vector>(point - line.point);

        if (vector_product(diff, vector) == Vector() && vector_product(vector, line.vector) == Vector())   
            return true;

        return false;
    }

    bool Line::operator!=(const Line& line) const
    {
        return operator==(line);
    }

    std::ostream& operator<<(std::ostream& out, const Line& l)
    {
        out << "Line(" << l.vector << ", " << l.point << ")";

        return out;
    }

    double calc_dist(const Point& point, const Line& line)
    {
        Vector p = Vector(point - line.point);

        double s_parallelogram = vector_product(p, line.vector).abs();
        
        return s_parallelogram / line.vector.abs();
    }

    bool equal_plane_side(const Point& p1, const Point& p2, const Line& line)
    {
        Vector v1 = Vector(line.point - p1);
        Vector v2 = Vector(line.point - p2);

        Vector v_dir1 = vector_product(line.vector, v1);
        Vector v_dir2 = vector_product(line.vector, v2);

        if (v_dir1 == Vector() || v_dir2 == Vector())
            return false;

        return v_dir1.normalize() == v_dir2.normalize();
    }
}
