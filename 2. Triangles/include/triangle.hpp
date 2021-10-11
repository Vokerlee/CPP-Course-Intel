#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "point.hpp"
#include "vector.hpp"

#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iostream>

namespace geom
{
    class Triangle
    {
    public:
        Point point1;
        Point point2;
        Point point3;

        Triangle(const Point& p,  const Vector& v1, const Vector& v2);
        Triangle(const Point& p1, const Point&  p2, const Point&  p3);

        bool operator==(const Triangle& tr) const;

        friend std::ostream& operator<<(std::ostream& out, const Triangle& p);
    };
}

#endif // !TRIANGLE_H_