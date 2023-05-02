// Unit tests for material 
#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <iostream> 
#include <vector>

#include "Common.hpp"
#include "Tuple.hpp"
#include "Material.hpp"


TEST_CASE("test_material_init", "material")
{
    Material mat;

    REQUIRE(mat.col == Color(1, 1, 1));
    REQUIRE(equal(mat.ambient, 0.1));
    REQUIRE(equal(mat.diffuse, 0.9));
    REQUIRE(equal(mat.specular, 0.9));
    REQUIRE(equal(mat.shininess, 200.0));
}
