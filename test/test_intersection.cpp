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


TEST_CASE("test_intersection_struct", "intersection")
{
    //Sphere sphere;    
    auto sphere = std::make_shared<Sphere>();
    float test_dist = 3.5f;

    std::cout << "[" << __func__ << "] sphere: " << sphere->toString() << std::endl; 

    Intersection test_intersection(sphere, test_dist);

    REQUIRE(equal_eps(test_intersection.t, test_dist, 1e-6));
    REQUIRE(test_intersection.target == sphere);
}

TEST_CASE("test_intersection_struct", "intersection")
