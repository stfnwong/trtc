/*
 * TEST_MATRIX
 * Unit tests for matrix object and operations 
 */


#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <vector>

#include "Common.hpp"
#include "Matrix.hpp"


TEST_CASE("test_matrix_ctor", "matrix")
{
    CHECK_NOTHROW(Matrix(4,4));
    CHECK_THROWS(Matrix(0, 0));
    CHECK_THROWS(Matrix(1, 0));
    CHECK_THROWS(Matrix(0, 1));
}

TEST_CASE("test_ones_matrix", "matrix")
{
    Matrix ones_test = ones(4,4);

    for(unsigned int rr = 0; rr < ones_test.nrows(); ++rr)
    {
        for(unsigned int cc = 0; cc < ones_test.ncols(); ++cc)
        {
            REQUIRE(ones_test(rr, cc) == 1.0);
        }
    }
}

TEST_CASE("test_matrix_init_with_vals", "matrix")
{
    std::vector<float> mat_values = {
        1,  2,  3,  4,
        5,  6,  7,  8,
        9,  10, 11, 12,
        13, 14, 15, 16
    };

    std::vector<float> too_few_vals = {1, 2, 3};
    CHECK_THROWS(Matrix(4,4, too_few_vals));

    Matrix val_mat(4, 4, mat_values);
    for(unsigned int rr = 0; rr < val_mat.nrows(); ++rr)
    {
        for(unsigned int cc = 0; cc < val_mat.ncols(); ++cc)
        {
            REQUIRE(equal(val_mat(rr, cc), mat_values[4 * rr + cc]));
        }
    }

    // Too many vals is fine since we only need the first mat.size()
    // vals to acutally exist (it is a waste of memory though)
    std::vector<float> too_many_vals = {
        1,  2,  3,  4,
        5,  6,  7,  8,
        9,  10, 11, 12,
        13, 14, 15, 16,
        17, 18, 19, 20
    };
    CHECK_NOTHROW(Matrix(2, 2), too_many_vals);
    CHECK_NOTHROW(Matrix(3, 3), too_many_vals);
    CHECK_NOTHROW(Matrix(2, 4), too_many_vals);
    
    // Create and check
    Matrix extra_val_mat(3, 3, too_many_vals);
    for(unsigned int rr = 0; rr < extra_val_mat.nrows(); ++rr)
    {
        for(unsigned int cc = 0; cc < extra_val_mat.ncols(); ++cc)
        {
            REQUIRE(equal(extra_val_mat(rr, cc), too_many_vals[3 * rr + cc]));
        }
    }
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

    // current implementation does bounds check
    // potential speedup by removing this
    CHECK_THROWS(mat(5,5));
    CHECK_THROWS(mat(4,4));
}


TEST_CASE("test_identity_matrix", "matrix")
{
    Matrix eye_exp(4, 4);

    eye_exp(0, 0) = 1.0;
    eye_exp(1, 1) = 1.0;
    eye_exp(2, 2) = 1.0;
    eye_exp(3, 3) = 1.0;

    Matrix eye_test = eye(4);
    
    REQUIRE(eye_test == eye_exp);
}


TEST_CASE("test_matrix_copy", "matrix")
{
    Matrix mat22_src(2, 2);
    Matrix mat22_dst(2, 2);

    mat22_src(0,0) = -3;
    mat22_src(0,1) = 5;
    mat22_src(1,0) = 1;
    mat22_src(1,1) = -2;

    REQUIRE(mat22_src != mat22_dst);
    mat22_dst = mat22_src;

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
        std::string("-3   5    \n") + 
        std::string("1    -2   \n");

    std::cout << "mat22 string length     : " << mat22.toString().length() << std::endl;
    std::cout << "exp_mat22 string length : " << exp_mat22_str.length() << std::endl;

    REQUIRE(mat22.toString() == exp_mat22_str);
}


// ================ ARITHMETIC ================ //
//TEST_CASE("test_matrix_multiply", "matrix")
//{
//    Matrix a_mat(4, 4);
//    Matrix b_mat(4, 4);
//
//    // Setup the two input matricies
//
//}
