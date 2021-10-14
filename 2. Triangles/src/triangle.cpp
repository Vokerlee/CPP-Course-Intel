#include "../include/point.hpp"
#include "../include/vector.hpp"
#include "../include/line.hpp"
#include "../include/triangle.hpp"

#include <vector>

namespace geom
{
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

    bool Triangle::contains(const Point& p) const
    {
        Vector a(point2, point1);
        Vector b(point3, point1);
        Vector c(p, point1);

        double k1 = vector_product(c, b).abs() / vector_product(a, b).abs();

        if (k1 >= -TOLERANCE && k1 <= 1 + TOLERANCE)
        {
            double k2 = (c - k1 * a).abs() / b.abs();

            if (k2 >= -TOLERANCE && (k1 + k2) <= 1 + TOLERANCE)
                return true;
        }

        return false;
    }

    bool Triangle::is_degenerate() const
    {
        Vector a(point3 - point1);
        Vector b(point2 - point1);

        if (vector_product(a, b) != Vector())
            return false;

        return true;
    }

    std::ostream& operator<<(std::ostream& out, const Triangle& tr)
    {
        out << "Triangle(" << tr.point1 << ", " << tr.point2 << ", " << tr.point3 << ")";

        return out;
    }

    bool intersect_triangle_pl(const Triangle& tr, const Point& p1, const Point& p2)
    {
        bool tr_outside    = equal_plane_side(tr.point1, tr.point2, Line(p1, p2)) && equal_plane_side(tr.point2, tr.point3, Line(p1, p2)); // здесь возможна ложь
        bool p1p2_outside1 = equal_plane_side(p1, p2, Line(tr.point1, tr.point2));
        bool p1p2_outside2 = equal_plane_side(p1, p2, Line(tr.point2, tr.point3));
        bool p1p2_outside3 = equal_plane_side(p1, p2, Line(tr.point3, tr.point1));

        return !tr_outside && (!p1p2_outside1 || !p1p2_outside2 || !p1p2_outside3);
    }

    bool intersect2D(const Triangle& tr1, const Triangle& tr2)
    {
        if (intersect_triangle_pl(tr1, tr2.point1, tr2.point2) ||
            intersect_triangle_pl(tr1, tr2.point2, tr2.point3) ||
            intersect_triangle_pl(tr1, tr2.point3, tr2.point1) ||
            intersect_triangle_pl(tr2, tr1.point1, tr1.point2) ||
            intersect_triangle_pl(tr2, tr1.point2, tr1.point3) ||
            intersect_triangle_pl(tr2, tr1.point3, tr1.point1))
        {
            return true;
        }

        return false;
    }

    bool intersect(const Triangle& tr1, const Triangle& tr2)
    {
    // Checking for degeneration (not being a triangle)
        if (tr1.is_degenerate() || tr2.is_degenerate())
            return false;

    // Triangles -> their planes
        Plane pl1(tr1);
        Plane pl2(tr2);

    // Rejecting the case when one of the thiangle is in the half-space of the plane of the other triangle
        double dist21n1 = calc_dist(tr2.point1, pl1);
        double dist21n2 = calc_dist(tr2.point2, pl1);
        double dist21n3 = calc_dist(tr2.point3, pl1);

        if ((dist21n1 >  Triangle::TOLERANCE && dist21n2 >  Triangle::TOLERANCE && dist21n3 >  Triangle::TOLERANCE) ||
            (dist21n1 < -Triangle::TOLERANCE && dist21n2 < -Triangle::TOLERANCE && dist21n3 < -Triangle::TOLERANCE))
            return false;

        double dist12n1 = calc_dist(tr1.point1, pl2);
        double dist12n2 = calc_dist(tr1.point2, pl2);
        double dist12n3 = calc_dist(tr1.point3, pl2);

        if ((dist12n1 >  Triangle::TOLERANCE && dist12n2 >  Triangle::TOLERANCE && dist12n3 >  Triangle::TOLERANCE) ||
            (dist12n1 < -Triangle::TOLERANCE && dist12n2 < -Triangle::TOLERANCE && dist12n3 < -Triangle::TOLERANCE))
            return false;

    // Checking for having 1 vertex in another triangle

        if ((std::abs(dist21n1) < Triangle::TOLERANCE && tr1.contains(tr2.point1)) ||
            (std::abs(dist21n2) < Triangle::TOLERANCE && tr1.contains(tr2.point2)) ||
            (std::abs(dist21n3) < Triangle::TOLERANCE && tr1.contains(tr2.point3)) ||
            (std::abs(dist12n1) < Triangle::TOLERANCE && tr2.contains(tr1.point1)) ||
            (std::abs(dist12n2) < Triangle::TOLERANCE && tr2.contains(tr1.point2)) ||
            (std::abs(dist12n3) < Triangle::TOLERANCE && tr2.contains(tr1.point3)))
        {
            return true;
        }

    // Case of intersection in common plane

        if (std::abs(dist21n1) < Triangle::TOLERANCE && std::abs(dist21n2) < Triangle::TOLERANCE && 
            std::abs(dist21n3) < Triangle::TOLERANCE)
        {
            return intersect2D(tr1, tr2); // already here there is no cases when one triangle is completely inside another
        }

    // Only 1 case is left: having common line of intersection

    // Line of intersections of two planes
        Line intersection_line(pl1, pl2);  // exist

    // Calc intervals and check for overlapping
        std::vector<double> params = calc_intervals(intersection_line, tr1, tr2);

        if ((std::min(params[2], params[3]) - std::max(params[0], params[1]) > -Triangle::TOLERANCE) ||
            (std::min(params[0], params[1]) - std::max(params[2], params[3]) > -Triangle::TOLERANCE))
            return false;

        return true; 
    }

    double calc_parameter(const Point& point, const Line& line)
    {
        Vector diff = static_cast<Vector>(point) - static_cast<Vector>(line.point);

        // Point must be on the line and diff is collinear to line.vector
        double tx = diff.x / line.vector.x;

        return tx;
    }

    std::vector<double> calc_intervals(const Line& l, const Triangle& tr1, const Triangle& tr2)
    {
        Plane pl1(tr1);
        Plane pl2(tr2);

        std::pair<Line, Line> lines = get_lines(tr1, pl2);
        
        // Lines which intersect plane
        Line l1 = lines.first;
        Line l2 = lines.second;

        // Calculate intersection points
        Point intersection_point_1(pl2, l1);
        Point intersection_point_2(pl2, l2);

        // Calculate parameter values
        double t11 = calc_parameter(intersection_point_1, l);
        double t12 = calc_parameter(intersection_point_2, l);

        // Now for the second triangle 
        lines = get_lines(tr2, pl1);
        l1 = lines.first;
        l2 = lines.second;

        intersection_point_1 = Point(pl1, l1);
        intersection_point_2 = Point(pl1, l2);

        double t21 = calc_parameter(intersection_point_1, l);
        double t22 = calc_parameter(intersection_point_2, l);

        return std::vector<double> {t11, t12, t21, t22};
    }

    std::pair<Line, Line> get_lines(const Triangle& t, const Plane& pl)
    {
        double da = calc_dist(t.point1, pl);
        double db = calc_dist(t.point2, pl);
        double dc = calc_dist(t.point3, pl);

        // Determine which lines intersect the plane
        Line l1;
        Line l2;

        // General situation
        if ((da <  Triangle::TOLERANCE && db <  Triangle::TOLERANCE && dc > -Triangle::TOLERANCE) || 
            (da > -Triangle::TOLERANCE && db > -Triangle::TOLERANCE && dc <  Triangle::TOLERANCE))
        {
            l1 = Line(t.point3, t.point1);
            l2 = Line(t.point3, t.point2);
        }
        else if ((da <  Triangle::TOLERANCE && db > -Triangle::TOLERANCE && dc <  Triangle::TOLERANCE) ||
                 (da > -Triangle::TOLERANCE && db <  Triangle::TOLERANCE && dc > -Triangle::TOLERANCE))
        {
            l1 = Line(t.point2, t.point1);
            l2 = Line(t.point2, t.point3);
        }
        else if ((da > -Triangle::TOLERANCE && db <  Triangle::TOLERANCE && dc <  Triangle::TOLERANCE) || 
                 (da <  Triangle::TOLERANCE && db > -Triangle::TOLERANCE && dc > -Triangle::TOLERANCE))
        {
            l1 = Line(t.point1, t.point2);
            l2 = Line(t.point1, t.point3);
        }

        return std::make_pair(l1, l2);
    }
}
