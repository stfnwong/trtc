// Unit tests for material 
#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <iostream> 
#include <vector>

#include "Color.hpp"
#include "Common.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Tuple.hpp"


TEST_CASE("test_material_init", "material")
{
    Material mat;

    REQUIRE(mat.col == Color(1, 1, 1));
    REQUIRE(equal(mat.ambient, 0.1));
    REQUIRE(equal(mat.diffuse, 0.9));
    REQUIRE(equal(mat.specular, 0.9));
    REQUIRE(equal(mat.shininess, 200.0));
}


TEST_CASE("test_light_with_eye_between_light_and_surface", "material")
{
    Material m;
    Tuple p = create_point(0, 0, 0);
    Tuple eyev = create_vector(0, 0, -1);
    Tuple normalv = create_vector(0, 0, -1);
    PointLight l = PointLight(create_point(0, 0, -10), Color(1, 1, 1));

    Color result = lighting(m, l, p, eyev, normalv);
    REQUIRE(result == Color(1.9, 1.9, 1.9));
}


TEST_CASE("test_light_with_eye_offset_between_light_and_surface", "material")
{
    Material m;
    Tuple p = create_point(0, 0, 0);
    Tuple eyev = create_vector(0, sqrt(2)/2.0f, sqrt(2)/2.0f);
    Tuple normalv = create_vector(0, 0, -1);
    PointLight l = PointLight(create_point(0, 0, -10), Color(1, 1, 1));

    Color result = lighting(m, l, p, eyev, normalv);
    REQUIRE(result == Color(1.0, 1.0, 1.0));
}

TEST_CASE("test_offset_light_with_eye_opposite_surface", "material")
{
    Material m;
    Tuple p = create_point(0, 0, 0);
    Tuple eyev = create_vector(0, 0, -1);
    Tuple normalv = create_vector(0, 0, -1);
    PointLight l = PointLight(create_point(0, 10, -10), Color(1, 1, 1));

    Color result = lighting(m, l, p, eyev, normalv);
    REQUIRE(result == Color(0.7364, 0.7364, 0.7364));
}


TEST_CASE("test_lighting_with_eye_in_path_of_reflection", "material")
{
    Material m;
    Tuple p = create_point(0, 0, 0);
    Tuple eyev = create_vector(0, -sqrt(2)/2.0f, -sqrt(2)/2.0f);
    Tuple normalv = create_vector(0, 0, -1);
    PointLight l = PointLight(create_point(0, 10, -10), Color(1, 1, 1));

    Color result = lighting(m, l, p, eyev, normalv);
    REQUIRE(result == Color(1.63639, 1.63639, 1.63639));
}

TEST_CASE("test_lighting_with_light_behind_surface", "material")
{
    Material m;
    Tuple p = create_point(0, 0, -1);
    Tuple eyev = create_vector(0, 0, -1);
    Tuple normalv = create_vector(0, 0, -1);
    PointLight l = PointLight(create_point(0, 0, 10), Color(1, 1, 1));

    Color result = lighting(m, l, p, eyev, normalv);
    REQUIRE(result == Color(0.1, 0.1, 0.1));
}
