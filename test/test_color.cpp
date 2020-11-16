/*
 * TEST_COLOR
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <iostream> 
#include <vector>

#include "Common.hpp"
#include "Color.hpp"


TEST_CASE("test_color_init", "infra")
{
    Color c_default;
    REQUIRE(c_default.r == 0.0);
    REQUIRE(c_default.g == 0.0);
    REQUIRE(c_default.b == 0.0);

    Color c_init(0.5, 0.6, 0.75);
    REQUIRE(equal(c_init.r, 0.5));
    REQUIRE(equal(c_init.g, 0.6));
    REQUIRE(equal(c_init.b, 0.75));
}

TEST_CASE("test_color_add", "infra")
{
    Color c1(0.9, 0.6, 0.75);
    Color c2(0.7, 0.1, 0.25);
    Color exp_color(1.6, 0.7, 1.0);

    Color sum_color = c1 + c2;

    REQUIRE(sum_color == exp_color);
}

TEST_CASE("test_color_subtract", "infra")
{
    Color c1(0.9, 0.6, 0.75);
    Color c2(0.7, 0.1, 0.25);
    Color exp_color(0.2, 0.5, 0.5);

    Color diff_color = c1 - c2;
    
    REQUIRE(diff_color == exp_color);
}

TEST_CASE("test_color_multiply", "infra")
{
    Color c1(1.0, 0.2, 0.4);
    Color c2(0.9, 1.0, 0.1);
    Color exp_color(0.9, 0.2, 0.04);

    Color mult_color = c1 * c2;

    REQUIRE(mult_color == exp_color);
}

// Conversions 
TEST_CASE("test_color_8bpp_string", "infra")
{
    Color c1(1.0, 0.2, 0.4);
    Color c2(2.9, 1.0, -0.1);       // ensure clamping 
    Color c3(-1.0, 0.5, 0.5);

    const std::string c1_exp_8bpp_string = "255 51 102";
    const std::string c2_exp_8bpp_string = "255 255 0";
    const std::string c3_exp_8bpp_string = "0 128 128";

    std::string c1_8bpp_string = c1.to8bppString();
    std::string c2_8bpp_string = c2.to8bppString();
    std::string c3_8bpp_string = c3.to8bppString();

    REQUIRE(c1_exp_8bpp_string == c1_8bpp_string);
    REQUIRE(c2_exp_8bpp_string == c2_8bpp_string);
    REQUIRE(c3_exp_8bpp_string == c3_8bpp_string);
}
