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
    return (point1 == point2 || point1 == point2 || point1 == point2);
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
        std::cout << "Checking if degenerate: " << std::endl;
        if (tr1.is_degenerate() || tr2.is_degenerate())
        {
            std::cout << "Degenerate.\n\n\n";
            return false;
        }

    // Triangles -> planes
        std::cout << "Computing plane equation of tr1..." << std::endl;
        Plane pl1(tr1);
        Plane pl2(tr2);

    // Calculate distances from tr2 vertices to pl1
        std::cout << "Computing distances from tr2 vertices to plane pl1..." << std::endl;

        double d1 = calc_dist(tr2.point1, pl1);
        double d2 = calc_dist(tr2.point2, pl1);
        double d3 = calc_dist(tr2.point3, pl1);

    // Having a vertice of tr1 in plane pl1 == no intersections
        if (std::abs(d1) < Triangle::TOLERANCE || std::abs(d2) < Triangle::TOLERANCE || std::abs(d3) < Triangle::TOLERANCE)
            return false;

    // If all the distances are of the same sign, exit
        if ((d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0))
        {
            std::cout << "All of the same size." << std::endl;
            return false;
        }

        std::cout << "Computing plane equation of tr2..." << std::endl;

    // If parallel, exit
        std::cout << "Checking if planes are parallel..." << std::endl;
        
        if (pl2.is_parallel(pl1) && !(pl2 == pl1))
            return false;

        if (pl2 == pl1)
            return true;

    // Compare distances from triangle tr1 to plane pl2. If they are all of the same sign, exit
        std::cout << "Computing distances from tr1 vertices to plane pl2...." << std::endl;

        float a1 = calc_dist(tr1.point1, pl2);
        float a2 = calc_dist(tr1.point2, pl2);
        float a3 = calc_dist(tr1.point3, pl2);

        if (std::abs(d1) < Triangle::TOLERANCE || std::abs(d2) < Triangle::TOLERANCE || std::abs(d3) < Triangle::TOLERANCE)
            return false;
        
    // If they are all of the same sign, exit
        if ((d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0))
        {
            std::cout << "All of the same sign." << std::endl;
            return false;
        }

    // Line of intersections
        std::cout << "Computing plane intersection line..." << std::endl;
        Line intersection_line(pl1, pl2);

    // Calc intervals and check intersection
        std::cout << "Computing intervals..." << std::endl;
        
        std::vector<double> params = calc_intervals(intersection_line, tr1, tr2);
        double t00 = params[0];
        double t01 = params[1];
        double t10 = params[2];
        double t11 = params[3];

        std::cout << "Calculated t values: " << std::endl;
        std::cout << t00 << ", " << t01 << ", " << t10 << ", " << t11 << std::endl;

        if (std::min(t10, t11) > std::max(t00, t01) || std::min(t00, t01) > std::max(t10, t11))
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
        Point intersection_point_1(pl1, l1);
        Point intersection_point_2(pl1, l2);

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

