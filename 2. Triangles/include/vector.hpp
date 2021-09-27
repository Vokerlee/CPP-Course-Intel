#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iostream>

namespace geom
{
    class Vector
    {
        static const size_t TOLERANCE = 1e-4;

    public:
        double x;
        double y;
        double z;

        Vector(double x_val = 0, double y_val = 0 , double z_val = 0);

        Vector(const Vector& source);
        void   operator= (const Vector& source);

        Vector operator+ (const Vector& source) const;
        Vector operator- (const Vector& source) const;
        void   operator+=(const Vector& source);
        void   operator-=(const Vector& source);
        Vector operator- ()                     const;

        bool   operator==(const Vector& source) const;
        bool   operator>=(const Vector& source) const;
        bool   operator> (const Vector& source) const;
        bool   operator<=(const Vector& source) const;
        bool   operator< (const Vector& source) const;

        Vector operator* (const double value)   const;
        Vector operator/ (const double value)   const;
        void   operator*=(const double value);
        void   operator/=(const double value);

        friend Vector operator*(const double value, const Vector& source);

        double abs() const;
        void normalize();
    };
}

#endif // !VECTOR_H_