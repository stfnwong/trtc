/* 
 * TEMPLATE MATRIX 
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <memory>
#include <iostream> 
#include <vector>

#include "Common.hpp"
#include "Tuple.hpp"
#include "TMatrix.hpp"


TEST_CASE("test_matrix_init_from_init_list", "matrix")
{
    TMatrix<2, 2> test_mat22 = TMatrix<2, 2>(
            {0.0f, 1.0f,
             1.0f, 0.0 }
    );

    REQUIRE(equal(test_mat22(0,0), 0.0f));
    REQUIRE(equal(test_mat22(0,1), 1.0f));
    REQUIRE(equal(test_mat22(1,1), 0.0f));
    REQUIRE(equal(test_mat22(1,0), 1.0f));
}


TEST_CASE("test_matrix_init_from_multi_init_list", "matrix")
{
    TMatrix<2, 2> test_mat22 = TMatrix<2, 2>(
            { {0.0f, 1.0f}, 
              {1.0f, 0.0f} }
    );

    REQUIRE(equal(test_mat22(0,0), 0.0f));
    REQUIRE(equal(test_mat22(0,1), 1.0f));
    REQUIRE(equal(test_mat22(1,1), 0.0f));
    REQUIRE(equal(test_mat22(1,0), 1.0f));
}


TEST_CASE("test_matrix_init_from_vector", "matrix")
{
    // make a 2,2 matrix and stick some garbage in it
    std::vector<float> mat_vals;
    mat_vals.reserve(2 * 2);        

    for(unsigned vv = 0; vv < (2 * 2); ++vv)
        mat_vals.emplace_back(float(vv));


    TMatrix<2, 2> test_mat22 = TMatrix<2, 2>(mat_vals);

    for(unsigned rr = 0; rr < 2; ++rr)
    {
        for(unsigned cc = 0; cc < 2; ++cc)
            REQUIRE(equal(test_mat22(rr, cc), mat_vals[rr * 2 + cc])); 
    }
}
