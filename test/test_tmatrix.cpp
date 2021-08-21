/* 
 * TEMPLATE MATRIX 
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <array>
#include <cmath>
#include <memory>
#include <iostream> 
#include <vector>

#include "Common.hpp"
#include "Tuple.hpp"
#include "TMatrix.hpp"


// ================ CTORS ================= // 
TEST_CASE("test_matrix_init", "matrix")
{
    TMatrix<8, 8> test_mat;

    std::array<int, 2> mat_shape = test_mat.shape();

    REQUIRE(mat_shape == std::array<int, 2>{8, 8});

    for(int rr = 0; rr < mat_shape[0]; ++rr)
    {
        for(int cc = 0; cc < mat_shape[1]; ++cc)
            REQUIRE(test_mat(rr, cc) == 0.0f);
    }
}

TEST_CASE("test_matrix_init_throws", "matrix")
{
    //CHECK_THROWS(TMatrix<0,0>());
    CHECK_THROWS(TMatrix<2,2>({1.0}));

    CHECK_THROWS(TMatrix<2,2>({1.0, 1.0, 1.0}));
    CHECK_THROWS(TMatrix<2,2>({1.0, 1.0, 1.0, 1.0, 1.0, 1.0}));
}

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

    for(int vv = 0; vv < (2 * 2); ++vv)
        mat_vals.emplace_back(float(vv));


    TMatrix<2, 2> test_mat22 = TMatrix<2, 2>(mat_vals);

    for(int rr = 0; rr < 2; ++rr)
    {
        for(int cc = 0; cc < 2; ++cc)
            REQUIRE(equal(test_mat22(rr, cc), mat_vals[rr * 2 + cc])); 
    }
}

TEST_CASE("test_mat2_init", "matrix")
{
    Mat2 test_mat2;

    std::array<int, 2> mat_shape = test_mat2.shape();
    REQUIRE(mat_shape == std::array<int, 2>{2, 2});

    for(int rr = 0; rr < mat_shape[0]; ++rr)
    {
        for(int cc = 0; cc < mat_shape[1]; ++cc)
            REQUIRE(test_mat2(rr, cc) == 0.0f);
    }
}

TEST_CASE("test_mat3_init", "matrix")
{
    Mat3 test_mat3;

    std::array<int, 2> mat_shape = test_mat3.shape();
    REQUIRE(mat_shape == std::array<int, 2>{3, 3});

    for(int rr = 0; rr < mat_shape[0]; ++rr)
    {
        for(int cc = 0; cc < mat_shape[1]; ++cc)
            REQUIRE(test_mat3(rr, cc) == 0.0f);
    }
}

TEST_CASE("test_mat4_init", "matrix")
{
    Mat4 test_mat4;

    std::array<int, 2> mat_shape = test_mat4.shape();
    REQUIRE(mat_shape == std::array<int, 2>{4, 4});

    for(int rr = 0; rr < mat_shape[0]; ++rr)
    {
        for(int cc = 0; cc < mat_shape[1]; ++cc)
            REQUIRE(test_mat4(rr, cc) == 0.0f);
    }
}


// ================ OPERATORS ================= // 
TEST_CASE("test_matrix_matrix_mul", "matrix")
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


    Mat4 a_mat(a_mat_vals);
    Mat4 b_mat(b_mat_vals);
    Mat4 exp_mat(exp_mat_vals);

    Mat4 out_mat;

    out_mat = a_mat * b_mat;
    REQUIRE(out_mat == exp_mat);
}


TEST_CASE("test_mat4_tuple_mul", "matrix")
{
    std::vector<float> a_mat_vals = {
        1, 2, 3, 4,
        2, 4, 4, 2,
        8, 6, 4, 1,
        0, 0, 0, 1
    };
    Mat4 a_mat(a_mat_vals);
    Tuple tuple(1, 2, 3, 1);

    Tuple exp_tuple(18, 24, 33, 1);
    Tuple out_tuple = a_mat * tuple;

    REQUIRE(out_tuple == exp_tuple);
}


// ================ UTILS ================= // 
TEST_CASE("test_submatrix_mat3", "matrix")
{
    std::vector<float> mat_values = {
        1,  5,  0,
        -3, 2,  7,
        0,  6, -3
    };
    Mat3 test_mat(mat_values);
    REQUIRE(test_mat.shape() == std::array<int, 2>{3, 3});

    std::vector<float> exp_submat_02_vals = {
        -3, 2,
        0,  6
    };
    Mat2 exp_submat_02(exp_submat_02_vals);
    Mat2 submat_02;

    submat_02 = test_mat.submatrix(0, 2);
    REQUIRE(submat_02 == exp_submat_02);
}

TEST_CASE("test_submatrix_mat4", "matrix")
{
    std::vector<float> mat_values = {
        1,  5, 1,  0,
        -3, 2, 1,  7,
        0,  6, 1, -3,
        1,  5, 2, -2
    };

    Mat4 test_mat(mat_values);

    std::vector<float> exp_submat_values = {
        1,  5,  0,
        0,  6, -3,
        1,  5, -2
    };

    Mat3 exp_sub_mat = Mat3(exp_submat_values);
    Mat3 sub_mat = test_mat.submatrix(1, 2);

    REQUIRE(sub_mat == exp_sub_mat);
}
