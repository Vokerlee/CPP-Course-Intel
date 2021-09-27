#include "../include/vector.hpp"

using namespace geom;

Vector::Vector(double x_val, double y_val , double z_val) :
    x(x_val), y(y_val), z(z_val)
{}

Vector::Vector(const Point& p1, const Point& p2)
{
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
}

Vector::Vector(const Vector& source)
{
    x = source.x;
    y = source.y;
    z = source.z;
}

void Vector::operator=(const Vector& source)
{
    x = source.x;
    y = source.y;
    z = source.z;
}

Vector Vector::operator+(const Vector& source) const
{
    return {source.x + x, source.y + y, source.z + z};
}

Vector Vector::operator-(const Vector& source) const
{
    return {x - source.x, y - source.y, z - source.z};
}

void Vector::operator+=(const Vector& source)
{
    x += source.x;
    y += source.y;
    z += source.z;
}

void Vector::operator-=(const Vector& source)
{
    x -= source.x;
    y -= source.y;
    z -= source.z;
}

Vector Vector::operator-() const
{
    return {-x, -y, -z};
}

bool Vector::operator==(const Vector& source) const
{
    return std::abs(this->abs() - source.abs()) < TOLERANCE;
}

bool Vector::operator>=(const Vector& source) const
{
    return (this->abs() - source.abs()) >= -TOLERANCE;
}

bool Vector::operator>(const Vector& source) const
{
    return (this->abs() - source.abs()) >= TOLERANCE;
}

bool Vector::operator<=(const Vector& source) const
{
    return (this->abs() - source.abs()) <= -TOLERANCE;
}

bool Vector::operator<(const Vector& source) const
{
    return (this->abs() - source.abs()) <= TOLERANCE;
}

Vector Vector::operator* (const double value) const
{
    return {x * value, y * value, z * value};
}

Vector Vector::operator/ (const double value) const
{
    return {x / value, y / value, z / value};
}

void Vector::operator*=(const double value)
{
    x *= value;
    y *= value;
    z *= value;
}

void Vector::operator/=(const double value)
{
    x /= value;
    y /= value;
    z /= value;
}

Vector operator*(const double value, const Vector& source)
{
    return {source.x * value, source.y * value, source.z * value};
}

double Vector::abs() const
{
    return std::sqrt(x * x + y * y + z * z);
}

namespace geom
{
    std::ostream& operator<<(std::ostream& out, const Vector& v)
    {
        out << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";

        return out;
    }
}