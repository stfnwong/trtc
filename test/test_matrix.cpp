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

TEST_CASE("test_matrix_copy", "matrix")
{
    Matrix mat22_src(2, 2);
    Matrix mat22_dst(2, 2);

    mat22_src(0,0) = -3;
    mat22_src(0,1) = 5;
    mat22_src(1,0) = 1;
    mat22_src(1,1) = -2;

    std::cout << "Before assignment: " << std::endl;
    std::cout << "mat22_src :  " << mat22_src.toString() << std::endl;
    std::cout << "mat22_dst :  " << mat22_dst.toString() << std::endl;

    REQUIRE(mat22_src != mat22_dst);
    mat22_dst = mat22_src;

    std::cout << "After assignment: " << std::endl;
    std::cout << "mat22_src :  " << mat22_src.toString() << std::endl;
    std::cout << "mat22_dst :  " << mat22_dst.toString() << std::endl;

    REQUIRE(mat22_src == mat22_dst);
}



TEST_CASE("test_matrix_compare", "matrix")
{
    Matrix mat22(2, 2);

    mat22(0,0) = -3;
    mat22(0,1) = 5;
    mat22(1,0) = 1;
    mat22(1,1) = -2;

    std::string exp_mat22_str = 
        std::string("Matrix(2,2)\n") + 
        std::string("-3   5 \n") + 
        std::string("1    -2 \n");

    REQUIRE(mat22.toString() == exp_mat22_str);
}
