/*
 * TEST INTERSECTION
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <memory>
#include <iostream> 
#include <vector>

#include "Common.hpp"
#include "Shape.hpp"
#include "Tuple.hpp"
#include "Intersection.hpp"


// Data structure tests 
TEST_CASE("test_intersection_struct", "intersection")
{
    //Sphere sphere;    
    auto sphere = std::make_shared<Sphere>();
    float test_dist = 3.5f;

    Intersection test_intersection(sphere, test_dist);

    REQUIRE(equal_eps(test_intersection.t, test_dist, 1e-6));
    REQUIRE(test_intersection.target == sphere);
}



// Ray intersection tests
TEST_CASE("test_ray_sphere_intersect_two_points", "ray")
{
    Tuple o = create_point(0, 0, -5);
    Tuple d = create_vector(0, 0, 1);

    Ray ray(o, d);
    auto sphere = std::make_shared<Sphere>();
    //Sphere sphere;

    REQUIRE(sphere->center == create_point(0,0,0));
    Intersections intersections = Intersect(sphere, ray);

    REQUIRE(intersections.count() == 2);
    REQUIRE(intersections[0].t == 4.0);
    REQUIRE(intersections[1].t == 6.0);
}

TEST_CASE("test_ray_sphere_intersect_tangent", "ray")
{
    Tuple o = create_point(0, 1, -5);
    Tuple d = create_vector(0, 0, 1);

    Ray ray(o, d);
    auto sphere = std::make_shared<Sphere>();
    //Sphere sphere;

    REQUIRE(sphere->center == create_point(0,0,0));

    Intersections intersections = Intersect(sphere, ray);

    REQUIRE(intersections.count() == 2);
    REQUIRE(intersections[0].t == 5.0);
    REQUIRE(intersections[1].t == 5.0);
}

TEST_CASE("test_ray_miss_sphere", "ray")
{
    Tuple o = create_point(0, 2, -5);
    Tuple d = create_vector(0, 0, 1);

    Ray ray(o, d);
    auto sphere = std::make_shared<Sphere>();
    //Sphere sphere;

    REQUIRE(sphere->center == create_point(0,0,0));
    REQUIRE(sphere->radius == 1.0);

    Intersections intersections = Intersect(sphere, ray);

    REQUIRE(intersections.count() == 0);
}



TEST_CASE("test_intersect_ray_sphere_with_new_structure", "intersection")
{
    Tuple o = create_point(0, 2, -5);
    Tuple d = create_vector(0, 0, 1);

    Ray ray(o, d);
    auto sphere = std::make_shared<Sphere>();
    //Sphere sphere;
    
    Intersections ray_intersections = Intersect(sphere, ray);
}



TEST_CASE("test_intersections_function", "intersection")
{
    auto sphere = std::make_shared<Sphere>();
    Intersection i1 = Intersection(sphere, 1.0);
    Intersection i2 = Intersection(sphere, 2.0);

    std::vector<Intersection> is_vector = std::vector<Intersection>{i1, i2};

    Intersections test_intersections = Intersections(is_vector);

    REQUIRE(test_intersections.count() == 2);
    REQUIRE(equal_eps(test_intersections[0].t, 1.0, 1e-6));
    REQUIRE(equal_eps(test_intersections[1].t, 2.0, 1e-6));
}
