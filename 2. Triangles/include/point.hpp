#ifndef POINT_H_
#define POINT_H_

#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iostream>

namespace geom
{
    class Vector;
    class Line;
    class Plane;

    class Point
    {
        constexpr static double TOLERANCE = 1e-4;

    public:
        double x;
        double y;
        double z;

        Point(double x_val = 0, double y_val = 0 , double z_val = 0);
        Point(const Plane& pl, const Line& l);

        Point operator-() const;
        Point operator+(const Point& source) const;
        Point operator-(const Point& source) const;

        bool operator==(const Point& source) const;
        bool operator!=(const Point& source) const;

        explicit operator Vector() const;

        friend std::ostream& operator<<(std::ostream& out, const Point& p);
    };
}

#endif // !POINT_H_