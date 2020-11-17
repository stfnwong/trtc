/*
 * TEST_MATRIX
 * Unit tests for matrix object and operations 
 */


#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include "Matrix.hpp"


TEST_CASE("test_matrix_ctor", "matrix")
{
    CHECK_NOTHROW(Matrix(4,4));
    CHECK_THROWS(Matrix(0, 0));
    CHECK_THROWS(Matrix(1, 0));
    CHECK_THROWS(Matrix(0, 1));
}

TEST_CASE("test_matrix_init", "matrix")
{
    Matrix mat(4, 4);

    REQUIRE(mat.nrows() == 4);
    REQUIRE(mat.ncols() == 4);

    std::cout << mat.toString() << std::endl;

    for(unsigned int r = 0; r < mat.nrows(); ++r)
    {
        for(unsigned c = 0; c < mat.ncols(); ++c)
            REQUIRE(mat(r, c) == 0.0);
    }
}

TEST_CASE("test_matrix_subscript", "matrix")
{
    Matrix mat(4, 4);

    REQUIRE(mat.nrows() == 4);
    REQUIRE(mat.ncols() == 4);

    mat(0, 0) = 1.0;
    REQUIRE(mat(0,0) == 1.0);

    mat(3, 3) = 1.0;
    REQUIRE(mat(3,3) == 1.0);

    CHECK_THROWS(mat(5,5));
    CHECK_THROWS(mat(4,4));
}
