#include "../include/plane.hpp"

using namespace geom;

Plane::Plane(const Point& p, const Vector& v1, const Vector& v2) :
    point(p),
    vector1(v1),
    vector2(v2)
{}

Plane::Plane(const Point& p1, const Point& p2, const Point& p3) :
    point(p1),
    vector1(p1, p2),
    vector2(p1, p3)
{}

Vector Plane::get_normal() const
{
    return vector_product(vector1, vector2);
}

bool Plane::operator==(const Plane& plane) const
{
    // Checking for collinear normals
    Vector normal1 = get_normal();
    Vector normal2 = plane.get_normal();

    Vector cross = vector_product(normal1, normal2);

    // Checking for coincidense

    Vector diff = static_cast<Vector>(point - plane.point);

    return (cross == Vector()) && 
           (std::abs(scalar_product(diff, normal1)) < TOLERANCE)) && 
           (std::abs(scalar_product(diff, normal2)) < TOLERANCE));
}

bool Plane::is_parallel(const Plane& plane) const
{
    // Checking for collinear normals
    Vector normal1 = get_normal();
    Vector normal2 = plane.get_normal();

    Vector cross = vector_product(normal1, normal2);

    return (cross == Vector());
}

namespace geom
{
    std::ostream& operator<<(std::ostream& out, const Plane& plane)
    {
        out << "(" << plane.point << ", " << plane.vector1 << ", " << plane.vector2 << ")";

        return out;
    }
}