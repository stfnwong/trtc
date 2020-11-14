/*
 * TEST_TUPLE
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <iostream> 
#include <iomanip>
#include <vector>
#include <string>

#include "Common.hpp"
#include "Tuple.hpp"


TEST_CASE("test_tuple_init", "infra")
{
    Tuple default_tuple;
    REQUIRE(default_tuple.x == 0.0);
    REQUIRE(default_tuple.y == 0.0);
    REQUIRE(default_tuple.z == 0.0);
    REQUIRE(default_tuple.w == 0.0);


    Tuple tst_point(4.3, -4.2, 3.1, 1.0);
    REQUIRE(equal(tst_point.x, 4.3));
    REQUIRE(equal(tst_point.y, -4.2));
    REQUIRE(equal(tst_point.z, 3.1));
    REQUIRE(equal(tst_point.w, 1.0));
}


// Factory tests 
TEST_CASE("test_point_factory", "infra")
{
    Tuple tst_point = create_point(4.3, -4.2, 3.1);
    Tuple exp_point(4.3, -4.2, 3.1, 0.0);

    REQUIRE(tst_point == exp_point);
}

TEST_CASE("test_vector_factory", "infra")
{
    Tuple tst_vector = create_vector(4.3, -4.2, 3.1);
    Tuple exp_vector(4.3, -4.2, 3.1, 1.0);

    REQUIRE(tst_vector == exp_vector);
}

// Arithmetic tests
TEST_CASE("test_tuple_plus", "infra")
{
    Tuple a_tuple(3, -2, 5, 1);
    Tuple b_tuple(-2, 3, 1, 0);
    Tuple exp_tuple(1, 1, 6, 1);
    Tuple sum_tuple = a_tuple + b_tuple;

    REQUIRE(exp_tuple == sum_tuple);
}

TEST_CASE("test_tuple_plus_assign", "infra")
{
    Tuple a_tuple(3, -2, 5, 1);
    Tuple b_tuple(-2, 3, 1, 0);
    Tuple exp_tuple(1, 1, 6, 1);

    a_tuple += b_tuple;
    REQUIRE(a_tuple == exp_tuple);
}

TEST_CASE("tets_tuple_minus", "infra")
{
    Tuple a_point(3, 2, 1);
    Tuple b_point(5, 6, 7);
    Tuple exp_point(-2, -4, -6);
    Tuple diff_point = a_point - b_point;

    REQUIRE(diff_point == exp_point);
}

TEST_CASE("test_tuple_minus_assign", "infra")
{
    Tuple a_point(3, 2, 1);
    Tuple b_point(5, 6, 7);
    Tuple exp_point(-2, -4, -6);

    a_point -= b_point;
    REQUIRE(a_point == exp_point);
}
