#ifndef POINT_H_
#define POINT_H_

#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iostream>

namespace geom
{
    class Point
    {
        static const size_t TOLERANCE = 1e-4;

    public:
        double x;
        double y;
        double z;

        Point(double x_val = 0, double y_val = 0 , double z_val = 0);

        Point(const Point& source);
        void operator= (const Point& source);

        Point operator-() const;

        bool operator==(const Point& source) const;

        friend std::ostream& operator<<(std::ostream& out, const Point& p);
    };
}

#endif // !POINT_H_