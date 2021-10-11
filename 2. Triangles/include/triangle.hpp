#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "point.hpp"
#include "vector.hpp"

#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace geom
{
    class Triangle
    {
        static const size_t TOLERANCE = 1e-5;

    public:
        Point point1;
        Point point2;
        Point point3;

        Triangle(const Point& p,  const Vector& v1, const Vector& v2);
        Triangle(const Point& p1, const Point&  p2, const Point&  p3);

        bool operator==(const Triangle& tr) const;
        bool is_degenerate() const;

        friend std::ostream& operator<<(std::ostream& out, const Triangle& p);
        friend bool intersect(const Triangle& tr1, const Triangle& tr2);
        friend std::vector<double> calc_intervals(const Line& l, const Triangle& tr1, const Triangle& tr2);
        friend double calc_parameter(const Point& point, const Line& line);
        friend std::pair<Line, Line> get_lines(const Triangle& t, const Plane& pl);
    };
}

#endif // !TRIANGLE_H_