/*
 * TEST RAY
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <iostream> 
#include <vector>

#include "Ray.hpp"
#include "Tuple.hpp"


TEST_CASE("test_ray_init", "ray")
{
    Tuple o = create_point(1, 2, 3);
    Tuple d = create_vector(4, 5, 2);

    Ray r(o, d);

    REQUIRE(r.origin == o);
    REQUIRE(r.direction == d);
}

