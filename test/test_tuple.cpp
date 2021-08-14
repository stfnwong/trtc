/*
 * TEST_TUPLE
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <iostream> 
#include <vector>

#include "Common.hpp"
#include "Tuple.hpp"


TEST_CASE("test_tuple_init", "infra")
{
    // the null point
    Tuple default_tuple;
    REQUIRE(default_tuple.x == 0.0);
    REQUIRE(default_tuple.y == 0.0);
    REQUIRE(default_tuple.z == 0.0);
    REQUIRE(default_tuple.w == 0.0);

    // a point
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
    Tuple exp_point(4.3, -4.2, 3.1, 1.0);

    REQUIRE(tst_point == exp_point);
}

TEST_CASE("test_vector_factory", "infra")
{
    Tuple tst_vector = create_vector(4.3, -4.2, 3.1);
    Tuple exp_vector(4.3, -4.2, 3.1, 0.0);

    REQUIRE(tst_vector == exp_vector);
}

// Arithmetic tests
TEST_CASE("test_point_vector_add", "infra")
{
    Tuple a_point(3, -2, 5, 1);
    Tuple b_vector(-2, 3, 1, 0);
    Tuple exp_tuple(1, 1, 6, 1);
    Tuple sum_tuple = a_point + b_vector;

    REQUIRE(exp_tuple == sum_tuple);
}

TEST_CASE("test_vector_vector_add", "infra")
{
    Tuple a_vector = create_vector(1, 2, 3);
    Tuple b_vector = create_vector(5, 6, 7);
    Tuple exp_result = create_vector(6, 8, 10);

    Tuple result = a_vector + b_vector;
    REQUIRE(result == exp_result);
}

TEST_CASE("test_point_subtract", "infra")
{
    Tuple a_point(3, 2, 1);
    Tuple b_point(5, 6, 7);
    Tuple exp_point(-2, -4, -6);
    Tuple diff_point = a_point - b_point;

    REQUIRE(diff_point == exp_point);
}

TEST_CASE("test_point_vector_subtract", "infra")
{
    Tuple point  = create_point(3, 2, 1);
    Tuple vector = create_vector(5, 6, 7);
    Tuple exp_result = create_point(-2, -4, -6);

    Tuple result = point - vector;

    REQUIRE(result == exp_result);
}

TEST_CASE("test_vector_vector_subtract", "infra")
{
    Tuple a_vector = create_vector(3, 2, 1);
    Tuple b_vector = create_vector(5, 6, 7);
    Tuple exp_result = create_vector(-2, -4, -6);

    Tuple result = a_vector - b_vector;
    REQUIRE(result == exp_result);
}

// Arithmetic and assign tests
TEST_CASE("test_vector_add_assign", "infra")
{
    Tuple a_vector(3, -2, 5, 1);
    Tuple b_vector(-2, 3, 1, 0);
    Tuple exp_tuple(1, 1, 6, 1);

    a_vector += b_vector;
    REQUIRE(a_vector == exp_tuple);
}

TEST_CASE("test_vector_vector_subtract_assign", "infra")
{
    Tuple a_vector = create_vector(3, 2, 1);
    Tuple b_vector = create_vector(5, 6, 7);
    Tuple exp_result = create_vector(-2, -4, -6);

    a_vector -= b_vector;
    REQUIRE(a_vector == exp_result);
}

TEST_CASE("test_point_subtract_assign", "infra")
{
    Tuple a_point(3, 2, 1);
    Tuple b_point(5, 6, 7);
    Tuple exp_point(-2, -4, -6);

    a_point -= b_point;
    REQUIRE(a_point == exp_point);
}

// Negation
TEST_CASE("test_point_negate", "infra")
{
    Tuple tst_point = create_point(1, 2, 3);
    Tuple exp_result = create_point(-1, -2, -3);

    REQUIRE(-tst_point == exp_result);
    Tuple zero_point = create_point(0, 0, 0);
    Tuple result = zero_point - tst_point;
    REQUIRE(result == exp_result);
}

TEST_CASE("test_vector_negate", "infra")
{
    Tuple tst_vector = create_vector(1, 2, 3);
    Tuple exp_result = create_vector(-1, -2, -3);

    REQUIRE(-tst_vector == exp_result);

    Tuple zero_vector = create_vector(0, 0, 0);
    Tuple result = zero_vector - tst_vector;
    REQUIRE(result == exp_result);
}

// Multiply/Divide
TEST_CASE("test_point_scalar_multiply", "infra")
{
    Tuple tst_point = create_point(2, 4, 6);
    Tuple exp_result = create_point(4, 8, 12);

    Tuple result = tst_point * 2;
    REQUIRE(result == exp_result);
}

TEST_CASE("test_point_scalar_divide", "infra")
{
    Tuple tst_point = create_point(2, 4, 6);
    Tuple exp_result = create_point(1, 2, 3);

    Tuple result = tst_point / 2;
    REQUIRE(result == exp_result);
}

TEST_CASE("test_vector_scalar_multiply", "infra")
{
    Tuple tst_vector = create_vector(2, 4, 6);
    Tuple exp_result = create_vector(1, 2, 3);

    Tuple result = tst_vector / 2;
    REQUIRE(result == exp_result);
}

TEST_CASE("test_vector_scalar_divide", "infra")
{
    Tuple tst_vector = create_vector(2, 4, 6);
    Tuple exp_result = create_vector(1, 2, 3);

    Tuple result = tst_vector / 2;
    REQUIRE(result == exp_result);
}

TEST_CASE("test_tuple_magnitude", "infra")
{
    const std::vector<Tuple> inp_tuples = { 
        Tuple(1, 0, 0),
        Tuple(0, 1, 0),
        Tuple(0, 0, 1),
        Tuple(1, 2, 3),
        Tuple(-1, -2, -3)
    };
    const std::vector<float> exp_results = {
        1,                  // (1, 0, 0)
        1,                  // (0, 1, 0)
        1,                  // (0, 0, 1)
        std::sqrt(static_cast<float>(14.0)),     // (1, 2, 3)
        std::sqrt(static_cast<float>(14.0))      // (-1, -2, -3)
    };

    for(unsigned int idx = 0; idx < inp_tuples.size(); ++idx)
        REQUIRE(inp_tuples[idx].mag() == exp_results[idx]);
}

TEST_CASE("test_tuple_norm", "infra")
{
    const std::vector<Tuple> inp_tuples = {
        Tuple(4, 0, 0),
        Tuple(1, 2, 3)
    };
    const std::vector<Tuple> exp_tuples = {
        Tuple(1, 0, 0),
        Tuple(1 / std::sqrt(static_cast<float>(14.0)), 
              2 / std::sqrt(static_cast<float>(14.0)), 
              3 / std::sqrt(static_cast<float>(14.0)))
    };
    const std::vector<float> exp_mags = {
        1,
        1
    };

    for(unsigned int idx = 0; idx < inp_tuples.size(); ++idx)
    {
        REQUIRE(inp_tuples[idx].norm() == exp_tuples[idx]);
        REQUIRE(equal(1.0, inp_tuples[idx].norm().mag()));
    }
}

TEST_CASE("test_vector_dot", "infra")
{
    Tuple v1 = create_vector(1, 2, 3);
    Tuple v2 = create_vector(2, 3, 4);
    float exp_result = 20.0;

    float result = v1.dot(v2);

    REQUIRE(equal(result, exp_result));

    // the standalone dot() method does the same thing 
    REQUIRE(equal(dot(v1, v2), exp_result));
}

TEST_CASE("test_vector_dot_2", "infra")
{
    Tuple a = create_vector(0, 1, -5);
    Tuple b = create_vector(0, 0, 1);

    float exp_result = -5.0;
    float result = dot(a, b);

    REQUIRE(equal(result, exp_result));
}

// These are all just combinations of dot products on points and vectors
TEST_CASE("test_vector_dot_3", "infra")
{
    Tuple a = create_point(0, 1, -5);
    Tuple b = create_point(0, 0, 1);

    float exp_result = -4.0;
    float result = dot(a, b);

    REQUIRE(equal(result, exp_result));
}

TEST_CASE("test_vector_dot_4", "infra")
{
    Tuple a = create_point(0, 1, -5);
    Tuple b = create_vector(0, 0, 1);

    float exp_result = -5.0;
    float result = dot(a, b);

    REQUIRE(equal(result, exp_result));
}

TEST_CASE("test_vector_dot_5", "infra")
{
    Tuple a = create_vector(0, 1, -5);
    Tuple b = create_point(0, 0, 1);

    float exp_result = -5.0;
    float result = dot(a, b);

    REQUIRE(equal(result, exp_result));
}

// Tuple cross product
TEST_CASE("test_vector_cross", "infra")
{
    Tuple v1 = create_vector(1, 2, 3);
    Tuple v2 = create_vector(2, 3, 4);

    REQUIRE(v1.cross(v2) == create_vector(-1, 2, -1));
    REQUIRE(v2.cross(v1) == create_vector(1, -2, 1));
}
