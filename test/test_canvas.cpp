/*
 * TEST_CANVAS
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <iostream> 
#include <vector>

#include "Common.hpp"
#include "Canvas.hpp"



TEST_CASE("test_canvas_init", "canvas")
{
    Canvas tst_canvas(32, 32);
    REQUIRE(tst_canvas.height() == 32);
    REQUIRE(tst_canvas.width() == 32);

    for(unsigned int h = 0; h < tst_canvas.height(); ++h)
    {
        for(unsigned int w = 0; w < tst_canvas.width(); ++w)
        {
            Color cur_color = tst_canvas.get(h, w);
            REQUIRE(cur_color == Color());
        }
    }
}

TEST_CASE("test_canvas_ppm_header", "canvas")
{
    Canvas canvas(5, 3);
    REQUIRE(canvas.height() == 3);
    REQUIRE(canvas.width() == 5);

    std::string exp_ppm_header = "P3\n5 3\n255\n";
    std::string out_ppm_string = canvas.toPPMString();
    std::string out_ppm_header = out_ppm_string.substr(0, exp_ppm_header.length());

    std::cout << "[exp_ppm_header]: " << std::endl << exp_ppm_header << std::endl;
    std::cout << "[out_ppm_header]: " << std::endl << out_ppm_header << std::endl;

    REQUIRE(exp_ppm_header == out_ppm_header);
}

TEST_CASE("test_canvas_ppm_format", "canvas")
{
    Canvas canvas(5, 3);
    REQUIRE(canvas.height() == 3);
    REQUIRE(canvas.width() == 5);

    Color c1(1.5, 0, 0);
    Color c2(0, 0.5, 0);
    Color c3(-0.5, 0, 1);

    canvas.set(0, 0, c1);
    canvas.set(2, 1, c2);
    canvas.set(4, 2, c3);

    std::string exp_ppm_string = std::string("P3\n5 3\n255\n\n") + 
        std::string("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n") +
        std::string("0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 \n") + 
        std::string("0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 \n");
    std::string out_ppm_string = canvas.toPPMString();

    std::cout << "[exp_ppm_string]: " << std::endl << exp_ppm_string << std::endl;
    std::cout << "[out_ppm_string]: " << std::endl << out_ppm_string << std::endl;

    REQUIRE(exp_ppm_string.length() == out_ppm_string.length());
    REQUIRE(exp_ppm_string == out_ppm_string);
}
