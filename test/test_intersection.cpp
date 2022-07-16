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
#include "Transform.hpp"


// Data structure tests 
TEST_CASE("test_intersection_struct", "intersection")
{
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

    REQUIRE(sphere->center == create_point(0,0,0));
    std::vector<Intersection> intersections = Intersect(sphere, ray);

    REQUIRE(intersections.size() == 2);
    REQUIRE(intersections[0].t == 4.0);
    REQUIRE(intersections[1].t == 6.0);
}

TEST_CASE("test_ray_sphere_intersect_tangent", "ray")
{
    Tuple o = create_point(0, 1, -5);
    Tuple d = create_vector(0, 0, 1);

    Ray ray(o, d);
    auto sphere = std::make_shared<Sphere>();

    REQUIRE(sphere->center == create_point(0,0,0));

    std::vector<Intersection> intersections = Intersect(sphere, ray);

    REQUIRE(intersections.size() == 2);
    REQUIRE(intersections[0].t == 5.0);
    REQUIRE(intersections[1].t == 5.0);
}

TEST_CASE("test_ray_miss_sphere", "ray")
{
    Tuple o = create_point(0, 2, -5);
    Tuple d = create_vector(0, 0, 1);

    Ray ray(o, d);
    auto sphere = std::make_shared<Sphere>();

    REQUIRE(sphere->center == create_point(0,0,0));
    REQUIRE(sphere->radius == 1.0);

    std::vector<Intersection> intersections = Intersect(sphere, ray);

    REQUIRE(intersections.size() == 0);
}


//TEST_CASE("test_intersect_ray_sphere_with_new_structure", "intersection")
//{
//    Tuple o = create_point(0, 2, -5);
//    Tuple d = create_vector(0, 0, 1);
//
//    Ray ray(o, d);
//    auto sphere = std::make_shared<Sphere>();
//    
//    std::vector<Intersection> ray_intersections = Intersect(sphere, ray);
//}


TEST_CASE("test_hit_all_positive_t", "intersection")
{
    auto sphere = std::make_shared<Sphere>();
    
    Intersection i1 = Intersection(sphere, 1.0);
    Intersection i2 = Intersection(sphere, 2.0);

    std::vector<Intersection> inp_intersections = std::vector<Intersection>{i1, i2};

    Intersection tt = Hit(inp_intersections);
    REQUIRE(tt == i1);
}

TEST_CASE("test_hit_all_negative_t", "intersection")
{
    auto sphere = std::make_shared<Sphere>();
    
    Intersection i1 = Intersection(sphere, -1.0);
    Intersection i2 = Intersection(sphere, -2.0);

    std::vector<Intersection> inp_intersections = std::vector<Intersection>{i1, i2};

    Intersection tt = Hit(inp_intersections);
    REQUIRE(tt == Intersection());  // All intersections are behind camera, therefore we expect an empty set
}

TEST_CASE("test_hit_some_positive_t", "intersection")
{
    auto sphere = std::make_shared<Sphere>();
    
    Intersection i1 = Intersection(sphere, -1.0);
    Intersection i2 = Intersection(sphere,  1.0);

    std::vector<Intersection> inp_intersections = std::vector<Intersection>{i1, i2};

    Intersection tt = Hit(inp_intersections);
    REQUIRE(tt == i2);
}


TEST_CASE("test_hit_is_always_lowest_nonnegative", "intersection")
{
    auto sphere = std::make_shared<Sphere>();
    
    std::vector<Intersection> inp_intersections = Intersections(
            Intersection(sphere, 5.0f),
            Intersection(sphere, 7.0f),
            Intersection(sphere, -3.0f),
            Intersection(sphere, 2.0f)
    );

    Intersection tt = Hit(inp_intersections);
    REQUIRE(tt == Intersection(sphere, 2.0f));
}

// Intersecting scaled spheres 
TEST_CASE("test_intersect_scaled_sphere_with_ray", "intersection")
{
    Tuple o = create_point(0, 0, -5);
    Tuple d = create_vector(0, 0, 1);
    Ray ray(o, d);
    auto s = std::make_shared<Sphere>();

    Matrix t = scale(2, 2, 2);
    s->set_transform(t);

    std::vector<Intersection> xs = Intersect(s, ray);

    for(unsigned i = 0; i < xs.size(); ++i)
    {
        std::cout << "xs[" << i << "]: " << xs[i].toString() << std::endl;
    }

    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == 3.0);
    REQUIRE(xs[1].t == 7.0);
}



TEST_CASE("test_intersect_translated_sphere_with_ray", "intersection")
{
    Tuple o = create_point(0, 0, -5);
    Tuple d = create_vector(0, 0, 1);
    Ray ray(o, d);
    auto s = std::make_shared<Sphere>();

    Matrix t = translate(5, 0, 0);
    s->set_transform(t);

    std::vector<Intersection> xs = Intersect(s, ray);
    REQUIRE(xs.size() == 0);
}
