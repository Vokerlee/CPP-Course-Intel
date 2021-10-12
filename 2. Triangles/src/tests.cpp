#include <gtest/gtest.h>

#include "triangle.hpp"
#include "line.hpp"
#include "vector.hpp"
#include "plane.hpp"
#include "point.hpp"

using namespace geom;

const double TOLERANCE = 1e-4;

//=========================================================

TEST(Triangles, PointEqual)
{
    Point p1(1.0, 2.1, 3.0);
    Point p2(1.0, 2.100000000001, 3.0);

    ASSERT_EQ(p1, p2);
}

//=========================================================

TEST(Triangles, VectorEqual)
{
    Point p1(1.0, 2.0, 3.0);
    Point p2(2.0, 1.0, 3.0);

    Vector v1(p1, p2);
    Vector v2(1.0, -1.0, 0.0);

    ASSERT_EQ(v1, v2);
}

//=========================================================

TEST(Triangles, VectorMulByNum)
{
    Vector v1(1.0, -1.0, 0.0);
    Vector v2 = v1 * 3;
    Vector v4 = 3 * v1;
    Vector v3(3.0, -3.0, 0.0);

    ASSERT_EQ(v3, v2);
    ASSERT_EQ(v4, v3);
}

//=========================================================

TEST(Triangles, TriangleConstructorVectors)
{
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(3, 2, 1);

    Triangle t1(p1, p2, p3);

    Vector v1(p1, p2);
    Vector v2(p1, p3);

    Triangle t2(p1, v1, v2);

    ASSERT_EQ(t1, t2);
}

//=========================================================

TEST(Triangles, LineConstructor)
{
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);

    Vector v1(2, -2, 3);

    Line l1(p1, v1);
    Line l2(p1, p2);

    ASSERT_EQ(l1, l2);
}

//=========================================================

TEST(Triangles, PlaneConstructor)
{
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Vector v1(p1, p2);
    Vector v2(p1, p3);

    Plane pl1(p1, p2, p3);
    Plane pl2(p1, v1, v2);

    ASSERT_EQ(pl1, pl2);
}

//=========================================================

TEST(Triangles, VectorProduct)
{
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Vector v1(p1, p2);
    Vector v2(p1, p3);

    Vector norm = vector_product(v1, v2);

    Vector res(7, -8, -10);
    ASSERT_EQ(norm, res);
}

//=========================================================

TEST(Triangles, ScalarProduct)
{
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Vector v1(p1, p2);
    Vector v2(p1, p3);

    double scalar = scalar_product(v1, v2);

    ASSERT_EQ(scalar, 5);
}

//=========================================================

TEST(Triangles, VectorConversion)
{
    Point p1(2, 1, -2);
    Point p2(4, -1, 1);
    Point p3(0, -2, -1);

    Vector v1(p1, p2);
    Vector v2(p1, p3);

    double scalar = scalar_product(v1, static_cast<Vector>(p1));

    ASSERT_EQ(scalar, -4);
}

//=========================================================

TEST(Triangles, TriangleNotDegenerate)
{
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(-1, -2, 0);

    Triangle t(p1, p2, p3);

    ASSERT_FALSE(t.is_degenerate());
}

//=========================================================

TEST(Triangles, TriangleDegenerate)
{
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(2, 0, 1);

    Triangle t(p1, p2, p3);

    ASSERT_TRUE(t.is_degenerate());
}

//=========================================================

TEST(Triangles, PointOperators)
{
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);

    Point p3(-1, 1, 0);
    Point p4(3, 1, 2);

    Point p5 = p1 - p2;
    Point p6 = p1 + p2;

    ASSERT_EQ(p5, p3);
    ASSERT_EQ(p6, p4);
}

//=========================================================

TEST(Triangles, PointPlaneDistance)
{
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(-1, -2, 0);

    Plane pl(p1, p2, p3);
    
    Point p(6, 10, -23);

    double dist = 25.7883;
    double computed_dist = calc_dist(p, pl);

    double precision = 1e-4;
    ASSERT_TRUE(std::abs(dist - computed_dist) < precision);
}

//=========================================================

TEST(Triangles, PointPlaneDistanceNegative)
{
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(-1, -2, 0);

    Plane pl(p1, p2, p3);
    
    Point p(-6, -10, 23);

    double dist = -24.6336;
    double computed_dist = calc_dist(p, pl);

    double precision = 1e-4;
    ASSERT_TRUE(std::abs(dist - computed_dist) < precision);
}

//=========================================================

TEST(Triangles, PlanePlaneParallel)
{
    Point p1(1, 1, 1);
    Point p2(3, 3, 3);
    Point p3(4, 1, 1);

    Point p4(2, 2, 2);
    Point p5(4, 4, 4);
    Point p6(8, 2, 2);

    Plane pl1(p1, p2, p3);
    Plane pl2(p4, p5, p6);
    
    ASSERT_TRUE(pl1.is_parallel(pl2));
    ASSERT_TRUE(pl1 == pl2);

    p4  = Point(-1, -1, 1);
    p5  = Point(-3, -3, 3);
    p6  = Point(-4, -1, 1);
    pl2 = Plane(p4, p5, p6);

    ASSERT_FALSE(pl1.is_parallel(pl2));
}

//=========================================================

TEST(Triangles, LinePlaneIntersection)
{
    Point A(1, 1, 1);
    Point B(2, 0, 1);
    Point C(-1, -2, 0);

    Point D(-1, 2, 5);
    Point E(2, 4, 2);
    Point F(1, -2, 0);

    Plane P0(A, B, C);
    Plane P1(D, E, F);
    Triangle t(D, E, F);

    double d1 = calc_dist(D, P0);
    double d2 = calc_dist(E, P0);
    double d3 = calc_dist(F, P0);

    ASSERT_FALSE((d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0));

    if (d1 < 0 && d2 < 0 && d3 > 0)
    {
        Line l1(D, F);
        Line l2(E, F);
    
        Point ans1(0.82609, -1.65217, 0.43478);
        Point ans2(1.66667, 2, 1.33333);  

        Point intersection_point_1(P0, l1);

        Point intersection_point_2(P0, l2);

        ASSERT_EQ(intersection_point_1, ans1);
        ASSERT_EQ(intersection_point_2, ans2);
    }
}

//=========================================================

TEST(Triangles, TrianglePlaneIntervals)
{
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(-1, -2, 0);

    Point p4(-1, 2, 5);
    Point p5(2, 4, 2);
    Point p6(1, -2, 0);

    Triangle t0(p1, p2, p3);
    Triangle t1(p4, p5, p6);

    Plane pl1(t1);
    Plane pl0(t0);

    Line intersection_line(pl0, pl1);

    std::pair<Line, Line> lines = get_lines(t0, pl1);
    
    Line l1 = lines.first;
    Line l2 = lines.second;

    Point intersection_point_1(pl1, l1);
    Point intersection_point_2(pl1, l2);

    ASSERT_EQ(intersection_point_1, Point(1.35484, 0.645161, 1.0000));
    ASSERT_EQ(intersection_point_2, Point(1.0625, -0.6250, 0.6875));

    double t11 = calc_parameter(intersection_point_1, intersection_line);
    double t12 = calc_parameter(intersection_point_2, intersection_line);

    ASSERT_TRUE(std::abs(t11 - 0.008575)    < TOLERANCE);
    ASSERT_TRUE(std::abs(t12 - (-0.001506)) < TOLERANCE);

    // Now for the second triangle

    lines = get_lines(t1, pl0);
    l1 = lines.first;
    l2 = lines.second;

    intersection_point_1 = Point(pl0, l1);
    intersection_point_2 = Point(pl0, l2);

    ASSERT_EQ(intersection_point_1, Point(0.826087, -1.65217, 0.434783));
    ASSERT_EQ(intersection_point_2, Point(1.66667, 2, 1.33333));

    double t21 = calc_parameter(intersection_point_1, intersection_line);
    double t22 = calc_parameter(intersection_point_2, intersection_line);

    ASSERT_TRUE(std::abs(t21 - (-0.009658)) < TOLERANCE);
    ASSERT_TRUE(std::abs(t22 - 0.019327) < TOLERANCE);
    
    bool intersect = true;

    if (std::min(t21, t22) > std::max(t11, t12) || std::min(t11, t12) > std::max(t21, t22))
        intersect = false;

    ASSERT_EQ(intersect, true);
}

//=========================================================

TEST(Triangles, TrianglePlaneIntersection1)
{
    Point p1(1, 1, 1);
    Point p2(2, 0, 1);
    Point p3(-1, -2, 0);

    Point p4(-1, 2, 5);
    Point p5(2, 4, 2);
    Point p6(1, -2, 0);

    Triangle t0(p1, p2, p3);
    Triangle t1(p4, p5, p6);

    ASSERT_TRUE(intersect(t0, t1));
}

//=========================================================

TEST(Triangles, TrianglePlaneIntersection2)
{
    Point p1(0, 0, 0);
    Point p2(1, 1, 1);
    Point p3(-1, 2, 1);

    Point p4(-1, 1, 0);
    Point p5(-3, -3, -3);
    Point p6(2, 1, 2);

    Triangle t0(p1, p2, p3);
    Triangle t1(p4, p5, p6);

    ASSERT_FALSE(intersect(t0, t1));
}

//=========================================================

TEST(Triangles, TrianglePlaneIntersection3)
{
    Point p1(1, 0, 0);
    Point p2(1, 1, 1);
    Point p3(-1, 2, 1);

    Point p4(-2, 1, 0);
    Point p5(-3, -3, -3);
    Point p6(2, 1, 2);

    Triangle t0(p1, p2, p3);
    Triangle t1(p4, p5, p6);

    ASSERT_FALSE(intersect(t0, t1));
}

//=========================================================

TEST(Triangles, TrianglePlaneIntersection4)
{
    Point p1(1, 0, 0);
    Point p2(1, 1, 1);
    Point p3(-1, 2, 1);

    Point p4(0, 1, 0);
    Point p5(-3, -3, -3);
    Point p6(2, 1, 2);

    Triangle t0(p1, p2, p3);
    Triangle t1(p4, p5, p6);

    ASSERT_TRUE(intersect(t0, t1));
}

//=========================================================

TEST(Triangles, TrianglePlaneIntersection5)
{
    Point p1(1, 0, 0);
    Point p2(1, 1, 1);
    Point p3(-1, 2, 1);

    Point p4(-1, 1, 0);
    Point p5(-3, -3, -3);
    Point p6(2, 1, 2);


    Triangle t0(p1, p2, p3);
    Triangle t1(p4, p5, p6);

    ASSERT_FALSE(intersect(t0, t1));
}

//=========================================================

TEST(Triangles, TrianglePlaneIntersection6)
{
    Point p1(1, 0, 0);
    Point p2(1, 1, 1);
    Point p3(-1, 2, 1);

    Point p4(-1.1, 1, 0);
    Point p5(-3, -3, -3);
    Point p6(2, 1, 2);

    Triangle t0(p1, p2, p3);
    Triangle t1(p4, p5, p6);

    ASSERT_FALSE(intersect(t0, t1));
}

//=========================================================

TEST(Triangles, TrianglePlaneIntersection7)
{
    Point p1(1, 0, 0);
    Point p2(1, 1, 1);
    Point p3(-1, 2, 1);

    Point p4(-1, 1.1, 0);
    Point p5(-3, -3, -3);
    Point p6(2, 1, 2);

    Triangle t0(p1, p2, p3);
    Triangle t1(p4, p5, p6);

    ASSERT_FALSE(intersect(t0, t1));
}

//=========================================================

TEST(Triangles, TrianglePlaneIntersection8)
{
    Point p1(1, 0, 0);
    Point p2(1, 1, 1);
    Point p3(-1, 2, 1);

    Point p4(0, 1, 0.5);
    Point p5(-3, -3, -3);
    Point p6(2, 1, 2);

    Triangle t0(p1, p2, p3);
    Triangle t1(p4, p5, p6);

    // Actually vertex belongs to the side of another triangle, this is yet to be decided whether to considet it an intersection or not
    ASSERT_FALSE(intersect(t0, t1));
}

//=========================================================

TEST(Triangles, TrianglePlaneIntersection9)
{
    Point p1(1, 0, 0);
    Point p2(1, 1, 1);
    Point p3(-1, 2, 1);

    Point p4(0, 1.01, 0.5);
    Point p5(-3, -3, -3);
    Point p6(2, 1, 2);

    Triangle t0(p1, p2, p3);
    Triangle t1(p4, p5, p6);

    // Here just slightly varying the 1.01 value, we get intersection segment
    ASSERT_TRUE(intersect(t0, t1));
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
