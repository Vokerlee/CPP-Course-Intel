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
        Point  point_;
        Vector vector_;

        Line(const Point& point,  const Vector& vector);
        Line(const Point& point1, const Point&  point2);

        Line(const Line& line);
        void operator=(const Line& line);

        bool operator==(const Line& line) const;

        friend std::ostream& operator<<(std::ostream& out, const Line& p);
    };
}

#endif // !LINE_H_