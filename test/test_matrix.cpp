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
            REQUIRE(equal(val_mat(rr, cc), mat_values[val_mat.nrows() * rr + cc]));
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
            REQUIRE(equal(extra_val_mat(rr, cc), too_many_vals[extra_val_mat.nrows() * rr + cc]));
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

    REQUIRE(mat22.toString() == exp_mat22_str);
}


// ================ ARITHMETIC ================ //
TEST_CASE("test_matrix_matrix_multiply", "matrix")
{
    std::vector<float> a_mat_vals = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6,
        5, 4, 3, 2
    };
    std::vector<float> b_mat_vals = {
        -2, 1, 2, 3,
        3,  2, 1, -1,
        4,  3, 6, 5,
        1,  2, 7, 8
    };
    std::vector<float> exp_mat_vals = {
        20, 22, 50,  48,
        44, 54, 114, 108,
        40, 58, 110, 102,
        16, 26, 46,  42
    };
    Matrix a_mat(4, 4, a_mat_vals);
    Matrix b_mat(4, 4, b_mat_vals);
    Matrix exp_mat(4, 4, exp_mat_vals);

    Matrix out_mat(4, 4);

    out_mat = a_mat * b_mat;
    REQUIRE(out_mat == exp_mat);

    // It should also be possible to multiply by any (4,N) matrix as well
    //Matrix c_mat = ones(4, 2);
    //std::cout << "c_mat : " << c_mat.toString() << std::endl;
    //Matrix c_mat_out(4, 2);
    ////Matrix c_mat_exp(4,2, c_mat_exp_vals);

    //c_mat_out = a_mat * c_mat;
    //std::cout << "c_mat_out : " << c_mat_out.toString() << std::endl;
    //REQUIRE(c_mat_out == a_mat);
}


TEST_CASE("test_matrix_tuple_multiply", "matrix")
{
    std::vector<float> a_mat_vals = {
        1, 2, 3, 4,
        2, 4, 4, 2,
        8, 6, 4, 1,
        0, 0, 0, 1
    };
    Matrix a_mat(4, 4, a_mat_vals);
    Tuple tuple(1, 2, 3, 1);

    Tuple exp_tuple(18, 24, 33, 1);
    Tuple out_tuple = a_mat * tuple;

    REQUIRE(out_tuple == exp_tuple);
}


TEST_CASE("test_matrix_transpose", "matrix")
{
    std::vector<float> inp_mat_vals = {
        0, 9, 3, 0,
        9, 8, 0, 8,
        1, 8, 5, 3,
        0, 0, 5, 8
    };
    std::vector<float> exp_mat_vals = {
        0, 9, 1, 0,
        9, 8, 8, 0,
        3, 0, 5, 5,
        0, 8, 3, 8
    };

    Matrix inp_mat(4, 4, inp_mat_vals);
    Matrix exp_mat(4, 4, exp_mat_vals);
    Matrix tr_mat(4, 4);

    tr_mat = inp_mat.transpose();
    REQUIRE(tr_mat == exp_mat);
}

TEST_CASE("test_matrix_2x2_determinant", "matrix")
{
    std::vector<float> mat_values = {1, 5, -3, 2};
    Matrix mat22(2, 2, mat_values);
    float exp_det = 17.0;

    float out_det = mat22.det();
    REQUIRE(equal(out_det, exp_det));
}

TEST_CASE("test_matrix33_submatrix", "matrix")
{
    std::vector<float> mat_values = {
        1,  5,  0,
        -3, 2,  7,
        0,  6, -3
    };
    Matrix test_mat(3, 3, mat_values);

    std::vector<float> exp_submat_02_vals = {
        -3, 2,
        0,  6
    };
    Matrix exp_submat_02(2, 2, exp_submat_02_vals);
    Matrix submat_02(2, 2);

    submat_02 = test_mat.submatrix(0, 2);
    REQUIRE(submat_02 == exp_submat_02);
}

TEST_CASE("test_matrix44_submatrix", "matrix")
{
    std::vector<float> mat_values = {
        -6, 1,  1, 6,
        -8, 5,  8, 6,
        -1, 0,  8, 2,
        -7, 1, -1, 1
    };
    Matrix test_mat(4, 4, mat_values);

    std::vector<float> exp_submat_33_vals = {
        -6, 1,  6,
        -8, 8,  6,
        -7, -1, 1
    };
    Matrix exp_submat_21(3, 3, exp_submat_33_vals);
    Matrix submat_21(3, 3);

    submat_21 = test_mat.submatrix(2, 1);
    REQUIRE(submat_21 == exp_submat_21);
}
