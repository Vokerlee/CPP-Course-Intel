#include "triangle.hpp"
#include <vector>

int main(int argc, char** argv)
{
    size_t n_triangles = 0;
    double x = NAN;
    double y = NAN;
    double z = NAN;

    std::cin >> n_triangles;

    std::vector<geom::Triangle> triangles;
    std::vector<geom::Point> points;

    for (size_t i = 0; i < n_triangles; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            std::cin >> x;
            std::cin >> y;
            std::cin >> z;

            points.push_back(geom::Point(x, y, z));
        }

        triangles.push_back(geom::Triangle(points[0], points[1], points[2]));

        points.clear();
    }

    return 0;
}