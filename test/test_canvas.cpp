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

