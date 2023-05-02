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

TEST_CASE("test_matrix_minor", "matrix")
{
    std::vector<float> mat_vals = {
        3,  5,  0,
        2, -1, -7,
        6, -1,  5
    };
    Matrix a_mat(3, 3, mat_vals);
    Matrix b_mat = a_mat.submatrix(1, 0);

    float exp_det = 25.0;
    float exp_minor = 25.0;

    REQUIRE(equal(b_mat.det(), exp_det));
    REQUIRE(equal(a_mat.minor(1, 0), exp_minor));
}

TEST_CASE("test_matrix_cofactor", "matrix")
{
    std::vector<float> mat_vals = {
        3,  5,  0,
        2, -1, -7,
        6, -1,  5
    };
    Matrix a_mat(3, 3, mat_vals);

    float exp_minor_00 = -12;
    float exp_cofactor_00 = -12;

    REQUIRE(equal(a_mat.minor(0, 0), exp_minor_00));
    REQUIRE(equal(a_mat.cofactor(0, 0), exp_cofactor_00));

    float exp_minor_10 = 25;
    float exp_cofactor_10 = -25;

    REQUIRE(equal(a_mat.minor(1, 0), exp_minor_10));
    REQUIRE(equal(a_mat.cofactor(1, 0), exp_cofactor_10));
}


TEST_CASE("test_matrix33_determinant", "matrix")
{
    std::vector<float> mat33_vals = {
         1, 2,  6,
        -5, 8, -4,
         2, 6,  4
    };
    Matrix a_mat(3, 3, mat33_vals);
    float exp_cofactor_00 = 56;
    float exp_cofactor_01 = 12;
    float exp_cofactor_02 = -46;
    float exp_det_33      = -196;

    REQUIRE(equal(a_mat.cofactor(0, 0), exp_cofactor_00));
    REQUIRE(equal(a_mat.cofactor(0, 1), exp_cofactor_01));
    REQUIRE(equal(a_mat.cofactor(0, 2), exp_cofactor_02));
    REQUIRE(equal(a_mat.det(), exp_det_33));
}

TEST_CASE("test_matrix44_determinant", "matrix")
{
    std::vector<float> mat44_vals = {
        -2, -8,  3,  5,
        -3,  1,  7,  3,
         1,  2, -9,  6,
        -6,  7,  7, -9
    };
    Matrix b_mat(4, 4, mat44_vals);
    float exp_cofactor_00 = 690;
    float exp_cofactor_01 = 447;
    float exp_cofactor_02 = 210;
    float exp_cofactor_03 = 51;
    float exp_det_44      = -4071;

    REQUIRE(equal(b_mat.cofactor(0, 0), exp_cofactor_00));
    REQUIRE(equal(b_mat.cofactor(0, 1), exp_cofactor_01));
    REQUIRE(equal(b_mat.cofactor(0, 2), exp_cofactor_02));
    REQUIRE(equal(b_mat.cofactor(0, 3), exp_cofactor_03));
    REQUIRE(equal(b_mat.det(), exp_det_44));
}

TEST_CASE("test_matrix_invertible", "matrix")
{
    std::vector<float> inv_vals = {
        6,  4, 4,  4,
        5,  5, 7,  6,
        4, -9, 3, -7,
        9,  1, 7, -6
    };
    Matrix mat_inv(4, 4, inv_vals);
    float exp_det_inv = -2120;

    REQUIRE(equal(mat_inv.det(), exp_det_inv));

    std::vector<float> non_inv_vals = {
        -4, 2, -2, -3,
        9,  6,  2,  6,
        0, -5,  1, -5,
        0,  0,  0,  0
    };
    Matrix mat_non_inv(4, 4, non_inv_vals);
    REQUIRE(equal(mat_non_inv.det(), 0.0));
}

TEST_CASE("test_matrix_invert", "matrix")
{
    std::vector<float> mat44_vals = {
        -5,  2,  6, -8,
        1,  -5,  1,  8,
        7,   7, -6, -7,
        1,  -3,  7,  4
    };
    Matrix mat44(4, 4, mat44_vals);
    Matrix mat44_inv = mat44.inverse();

    float exp_det         = 532.0;
    float exp_cofactor_23 = -160.0;
    float exp_b32         = -160.0 / 532.0;
    float exp_cofactor_32 = 105.0;
    float exp_b23         = 105.0 / 532.0;

    std::vector<float> mat44_inv_vals = {
         0.21805,  0.45113,  0.24060, -0.04511,
        -0.80827, -1.45677, -0.44361,  0.52068,
        -0.07895, -0.22368, -0.05263,  0.19737,
        -0.52256, -0.81391, -0.30075,  0.30639
    };
    Matrix mat44_exp_inv(4, 4, mat44_inv_vals); 

    REQUIRE(equal(mat44.det(), exp_det));

    REQUIRE(equal(mat44.cofactor(2, 3), exp_cofactor_23));
    REQUIRE(equal(mat44.cofactor(3, 2), exp_cofactor_32));
    REQUIRE(equal(mat44_inv(3, 2), exp_b32));
    REQUIRE(equal(mat44_inv(2, 3), exp_b23));

    REQUIRE(mat44_inv == mat44_exp_inv);

    // Some more matricies 
    std::vector<float> c_mat_vals = {
         8, -5,  9,  2, 
         7,  5,  6,  1,
        -6,  0,  9,  6,
        -3,  0, -9, -4
    };
    Matrix c_mat(4, 4, c_mat_vals);

    std::vector<float> c_mat_inv_vals = {
        -0.15385, -0.15385, -0.28205, -0.53846,
        -0.07692,  0.12308,  0.02564,  0.03077,
         0.35897,  0.35897,  0.43590,  0.92308,
        -0.69231, -0.69231, -0.76923, -1.92308
    };
    Matrix exp_c_mat_inv(4, 4, c_mat_inv_vals);
    Matrix c_mat_inv = c_mat.inverse();

    REQUIRE(c_mat_inv == exp_c_mat_inv);

    // Another matrix
    std::vector<float> d_mat_vals = {
         9,  3,  0,  9,
        -5, -2, -6, -3,
        -4,  9,  6,  4,
        -7,  6,  6,  2
    };
    Matrix d_mat(4, 4, d_mat_vals);
    
    std::vector<float> d_mat_inv_vals = {
        -0.04074, -0.07777,  0.14444, -0.22222,
        -0.07778,  0.03333,  0.36667, -0.33333,
        -0.02901, -0.14630, -0.10926,  0.12963,
         0.17778,  0.06667, -0.26667,  0.33333
    };
    Matrix exp_d_mat_inv(4, 4, d_mat_inv_vals);
    Matrix d_mat_inv = d_mat.inverse();

    REQUIRE(d_mat_inv == exp_d_mat_inv);
}

TEST_CASE("test_matrix_invert_and multiply", "matrix")
{
    std::vector<float> a_vals = {
        3, -9, 7, 3,
        3, -8, 2, -9,
        -4, 4, 4, 1,
        -6, 5, -1, 1
    };
    Matrix a_mat(4, 4, a_vals);

    std::vector<float> b_vals = {
        8,  2, 2, 2,
        3, -1, 7, 0,
        7,  0, 5, 4, 
        6, -2, 0, 5
    };
    Matrix b_mat(4, 4, b_vals);

    Matrix c_mat = a_mat * b_mat;
    Matrix a_mat_inv = c_mat * b_mat.inverse();

    REQUIRE(a_mat_inv == a_mat);
}
