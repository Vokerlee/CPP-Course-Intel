#include "../include/point.hpp"
#include "../include/vector.hpp"
#include "../include/line.hpp"
#include "../include/triangle.hpp"

#include <vector>

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

bool Triangle::is_degenerate() const
{
    Vector a(point3 - point1);
    Vector b(point2 - point1);

    if (vector_product(a, b) != Vector())
        return false;

    return true;
}

namespace geom
{
    std::ostream& operator<<(std::ostream& out, const Triangle& tr)
    {
        out << "Triangle(" << tr.point1 << ", " << tr.point2 << ", " << tr.point3 << ")";

        return out;
    }

    bool intersect(const Triangle& tr1, const Triangle& tr2) 
    {
    // Checking for degeneration (not being a triangle)
        if (tr1.is_degenerate() || tr2.is_degenerate())
            return false;

    // Triangles -> planes
        Plane pl1(tr1);
        Plane pl2(tr2);

    // Calculate distances from tr2 vertices to pl1
        double d1 = calc_dist(tr2.point1, pl1);
        double d2 = calc_dist(tr2.point2, pl1);
        double d3 = calc_dist(tr2.point3, pl1);

    // Having a vertice of tr1 in plane pl1 == no intersections
        if (std::abs(d1) < Triangle::TOLERANCE || std::abs(d2) < Triangle::TOLERANCE || std::abs(d3) < Triangle::TOLERANCE)
            return false;

    // If all the distances are of the same sign, exit
        if ((d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0))
            return false;

    // If parallel, exit
        if (pl2 == pl1)
            return true;

        if (pl2.is_parallel(pl1))
            return false;

    // Compare distances from triangle tr1 to plane pl2. If they are all of the same sign, exit
        double a1 = calc_dist(tr1.point1, pl2);
        double a2 = calc_dist(tr1.point2, pl2);
        double a3 = calc_dist(tr1.point3, pl2);

        if (std::abs(d1) < Triangle::TOLERANCE || std::abs(d2) < Triangle::TOLERANCE || std::abs(d3) < Triangle::TOLERANCE)
            return false;
        
    // If they are all of the same sign, exit
        if ((d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0))
            return false;

    // Line of intersections
        Line intersection_line(pl1, pl2);

    // Calc intervals and check intersection
        std::vector<double> params = calc_intervals(intersection_line, tr1, tr2);

        // std::cout << "Calculated t values: \n\n" << std::endl;
        // std::cout << t00 << ", " << t01 << ", " << t10 << ", " << t11 << std::endl;

        if (std::min(params[2], params[3]) > std::max(params[0], params[1]) || std::min(params[0], params[1]) > std::max(params[2], params[3]))
            return false;
        else
            return true; 
    }

    double calc_parameter(const Point& point, const Line& line)
    {
        Vector diff = static_cast<Vector>(point) - static_cast<Vector>(line.point);

        // Point must be on the line and diff is collinear to line.vector
        double tx = diff.x / line.vector.x;
        double ty = diff.y / line.vector.y;
        double tz = diff.z / line.vector.z;

        assert(std::abs(tx - ty) < Triangle::TOLERANCE && std::abs(ty - tz) < Triangle::TOLERANCE && std::abs(tx - tz) < Triangle::TOLERANCE);

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

        if ((da < 0 && db < 0 && dc > 0) || (da > 0 && db > 0 && dc < 0) )
        {
            l1 = Line(t.point3, t.point1);
            l2 = Line(t.point3, t.point2);
        }
        else if ((da < 0 && db > 0 && dc < 0) || (da > 0 && db < 0 && dc > 0))
        {
            l1 = Line(t.point2, t.point1);
            l2 = Line(t.point2, t.point3);
        }
        else if ((da > 0 && db < 0 && dc < 0) || (da < 0 && db > 0 && dc > 0))
        {
            l1 = Line(t.point1, t.point2);
            l2 = Line(t.point1, t.point3);
        }

        // Cases where point belongs to the plane
        if (std::abs(da) < Triangle::TOLERANCE)
        {
            l1 = Line(t.point2, t.point1);
            l2 = Line(t.point2, t.point3);
        }
        else if (std::abs(db) < Triangle::TOLERANCE)
        {
            l1 = Line(t.point1, t.point2);
            l2 = Line(t.point1, t.point3);
        }
        else if (std::abs(dc) < Triangle::TOLERANCE)
        {
            l1 = Line(t.point1, t.point3);
            l2 = Line(t.point1, t.point2);
        }

        return std::make_pair(l1, l2);
    }
}
