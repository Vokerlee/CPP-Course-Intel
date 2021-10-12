#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iostream>

namespace geom
{
    class Point;
    
    class Vector
    {
        constexpr static double TOLERANCE = 1e-5;

    public:
        double x;
        double y;
        double z;

        Vector(double x_val = 0, double y_val = 0 , double z_val = 0);
        Vector(const Point& p1, const Point& p2);

        Vector operator+ (const Vector& source) const;
        Vector operator- (const Vector& source) const;
        void   operator+=(const Vector& source);
        void   operator-=(const Vector& source);
        Vector operator- ()                     const;

        bool   operator==(const Vector& source) const;
        bool   operator!=(const Vector& source) const;
        bool   operator>=(const Vector& source) const;
        bool   operator> (const Vector& source) const;
        bool   operator<=(const Vector& source) const;
        bool   operator< (const Vector& source) const;

        Vector operator* (const double value)   const;
        Vector operator/ (const double value)   const;
        void   operator*=(const double value);
        void   operator/=(const double value);

        friend Vector operator*(const double value, const Vector& source);

        friend std::ostream& operator<<(std::ostream& out, const Vector& v);

        double abs() const;
        Vector& normalize();
    };

    Vector vector_product(const Vector& v1, const Vector& v2);
    double scalar_product(const Vector& v1, const Vector& v2);
}

#endif // !VECTOR_H_