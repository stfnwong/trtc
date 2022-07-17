/*
 * TEST_SHAPE
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <iostream> 
#include <vector>

#include "Common.hpp"
#include "Transform.hpp"
#include "Shape.hpp"



TEST_CASE("test_sphere_normal", "sphere_normal")
{
    Sphere s;
    Tuple n;
    Tuple test_point;

    // x-axis normal
    test_point = create_point(1, 0, 0);
    n = s.normal_at(test_point);
    REQUIRE(n == create_vector(1, 0, 0));

    // y-axis normal
    test_point = create_point(0, 1, 0);
    n = s.normal_at(test_point);
    REQUIRE(n == create_vector(0, 1, 0));

    // z-axis normal
    test_point = create_point(0, 0, 1);
    n = s.normal_at(test_point);
    REQUIRE(n == create_vector(0, 0, 1));

    // another normal
    test_point = create_point(sqrt(3.0)/3, sqrt(3.0)/3, sqrt(3.0)/3);
    n = s.normal_at(test_point);
    REQUIRE(n == create_vector(sqrt(3.0)/3, sqrt(3.0)/3, sqrt(3.0)/3));

}

TEST_CASE("test_translated_sphere_normal", "sphere_normal")
{
    Tuple n;
    Sphere s;

    // Normal of translated sphere 
    s.set_transform(translate(0, 1, 0));
    n = s.normal_at(create_point(0, 1.70711, -0.70711));
    REQUIRE(n == create_vector(0, 0.70711, -0.70711));


    // Normal of scaled sphere
    s.set_transform(scale(1, 0.5, 1) * rotate_z(M_PI / 5.0));
    n = s.normal_at(create_point(0, sqrt(2.0)/2, -sqrt(2.0)/2));
    REQUIRE(n == create_vector(0, 0.97014, -0.24254));
}
