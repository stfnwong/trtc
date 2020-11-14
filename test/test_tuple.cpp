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
    Tuple tst_point(4.3, -4.2, 3.1, 1.0);
    REQUIRE(equal(tst_point.x, 4.3));
    REQUIRE(equal(tst_point.y, -4.2));
    REQUIRE(equal(tst_point.z, 3.1));
    REQUIRE(equal(tst_point.w, 1.0));
}



TEST_CASE("test_point_factory", "infra")
{
    Tuple tst_point = create_point(4.3, -4.2, 3.1);
    Tuple exp_point = Tuple(4.3, -4.2, 3.1, 0.0);

    std::cout << "Created new tuple " << tst_point.toString() << std::endl;

    REQUIRE(tst_point == exp_point);
}

TEST_CASE("test_vector_factory", "infra")
{
    Tuple tst_vector = create_vector(4.3, -4.2, 3.1);
    Tuple exp_vector = Tuple(4.3, -4.2, 3.1, 1.0);

    std::cout << "Created new tuple " << tst_vector.toString() << std::endl;

    REQUIRE(tst_vector == exp_vector);
}
