#ifndef LINE_H_
#define LINE_H_

#include "point.hpp"
#include "vector.hpp"

#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iostream>

namespace geom
{
    class Line
    {
    public:
        Point  point;
        Vector vector;

        Line(const Point& p,  const Vector& v);
        Line(const Point& p1, const Point& p2);

        Line(const Line& line);
        void operator=(const Line& line);

        bool operator==(const Line& line) const;

        friend std::ostream& operator<<(std::ostream& out, const Line& p);
    };
}

#endif // !LINE_H_