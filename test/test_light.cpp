// Unit tests for lights 
#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <iostream> 
#include <vector>

#include "Common.hpp"
#include "Tuple.hpp"
#include "Light.hpp"


TEST_CASE("test_tuple_init", "infra")
{
    Tuple pos = create_point(0, 0, 0);
    Color col = Color(1, 1, 1);

    PointLight light = PointLight(pos, col);

    REQUIRE(light.pos == pos);
}
