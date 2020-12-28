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

TEST_CASE("test_ray_position", "ray")
{
    Tuple o = create_point(2, 3, 4);
    Tuple d = create_vector(1, 0, 0);

    Ray ray(o, d);

    const std::vector<float> inp_positions = {
        0, 1, -1, 2.5
    };
    const std::vector<Tuple> exp_positions = {
        create_point(2, 3, 4),
        create_point(3, 3, 4),
        create_point(1, 3, 4),
        create_point(4.5, 3, 4)
    };

    for(unsigned int idx = 0; idx < inp_positions.size(); ++idx)
        REQUIRE(ray.position(inp_positions[idx]) == exp_positions[idx]);
}
