#ifndef PLANE_H_
#define PLANE_H_

#include "point.hpp"
#include "vector.hpp"

#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iostream>

namespace geom
{
    class Plane
    {
        static const size_t TOLERANCE = 1e-5;

    public:
        Point  point;
        Vector vector1;
        Vector vector2;

        Plane(const Point& p,  const Vector& v1, const Vector& v2);
        Plane(const Point& p1, const Point&  p2, const Point&  p3);

        bool operator== (const Plane& plane) const;
        bool is_parallel(const Plane& plane) const;

        Vector get_normal() const;

        friend std::ostream& operator<<(std::ostream& out, const Plane& p);
    };
}

#endif // !PLANE_H_