#include "../include/vector.hpp"
#include "../include/point.hpp"

namespace geom
{
    Vector::Vector(double x_val, double y_val , double z_val) :
        x(x_val), y(y_val), z(z_val)
    {}

    Vector::Vector(const Point& p1, const Point& p2)
    {
        x = p2.x - p1.x;
        y = p2.y - p1.y;
        z = p2.z - p1.z;
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
        
        return (std::abs(source.x - x) < TOLERANCE && std::abs(source.y - y) < TOLERANCE &&
                std::abs(source.z - z) < TOLERANCE);
    }

    bool Vector::operator!=(const Vector& source) const
    {
        return !operator==(source);
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

    Vector Vector::operator*(const double value) const
    {
        return {x * value, y * value, z * value};
    }

    Vector Vector::operator/(const double value) const
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

    double Vector::abs() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector& Vector::normalize()
    {
        double abs = this->abs();
        x = x / abs;
        y = y / abs;
        z = z / abs;

        return *this;
    }

    Vector operator*(const double value, const Vector& source)
    {
        return {source.x * value, source.y * value, source.z * value};
    }

    std::ostream& operator<<(std::ostream& out, const Vector& v)
    {
        out << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";

        return out;
    }

    Vector vector_product(const Vector& v1, const Vector& v2)
    {
        double x = v1.y * v2.z - v1.z * v2.y;
        double y = v1.z * v2.x - v1.x * v2.z;
        double z = v1.x * v2.y - v1.y * v2.x;

        return Vector(x, y, z);
    }

    double scalar_product(const Vector& v1, const Vector& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }
}
