/*
 * TEST_TRANSFORM
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include <cmath>
#include <iostream> 
#include <vector>

#include "Transform.hpp"


// ======== TRANSLATE ======== // 
TEST_CASE("test_translate", "translate")
{
    // GIVEN: A point and a translation matrix
    // WHEN: That point is multiplied by the translation matrix 
    // THEN: The point is translated
    Tuple p1 = create_point(-3, 4, 5);
    Tuple exp_point = create_point(2, 1, 7);

    Matrix translation_mat = translate(5, -3, 2);

    Tuple out_point = translation_mat * p1;

    REQUIRE(out_point == exp_point);
}

TEST_CASE("test_translate_inverse", "translate")
{
    // GIVEN: A point and a translation matrix
    // WHEN: That point is multiplied by the inverse of the translation matrix 
    // THEN: The point moves in reverse
    Tuple p1 = create_point(-3, 4, 5);
    Tuple exp_point = create_point(-8, 7, 3);

    Matrix translation_mat = translate(5, -3, 2);
    Matrix translation_inv = translation_mat.inverse();
    Tuple out_point = translation_inv * p1;

    REQUIRE(out_point == exp_point);
}

TEST_CASE("test_translate_does_not_affect_vectors", "translate")
{
    // GIVEN: A vector and a translation matrix
    // WHEN: That vector is multiplied by the translation matrix 
    // THEN: The vector remains unchanged
    Tuple v1 = create_vector(-3, 4, 5);
    Matrix translation_mat = translate(5, -3, 2);

    Tuple t_vec = translation_mat * v1;

    REQUIRE(t_vec == v1);
}

// ======== SCALE ======== // 
TEST_CASE("test_scale_point", "scale")
{
    // GIVEN: A point and a scaling matrix
    // WHEN: That point is multiplied by the translation matrix 
    // THEN: The point becomes scaled
    Tuple p1 = create_point(-4, 6, 8);
    Matrix scale_mat = scale(2, 3, 4);
    Tuple exp_point = create_point(-8, 18, 32);

    Tuple out_point = scale_mat * p1;

    REQUIRE(out_point == exp_point);
}

TEST_CASE("test_scale_vector", "scale")
{
    // GIVEN: A vector and a scaling matrix
    // WHEN: That vector is multiplied by the translation matrix 
    // THEN: The vector becomes scaled
    Tuple v1 = create_vector(-4, 6, 8);
    Matrix scale_mat = scale(2, 3, 4);
    Tuple exp_vector = create_vector(-8, 18, 32);

    Tuple out_vector = scale_mat * v1;

    REQUIRE(out_vector == exp_vector);
}

TEST_CASE("test_scale_vector_inverse", "scale")
{
    // GIVEN: A vector and a scaling matrix
    // WHEN: That vector is multiplied by the scaling matrix 
    // THEN: The vector is scaled
    Tuple v1 = create_vector(-4, 6, 8);
    Matrix scale_mat = scale(2, 3, 4);
    Tuple exp_vector = create_vector(-2, 2, 2);
    Matrix scale_inv = scale_mat.inverse();

    Tuple out_vector = scale_inv * v1;

    REQUIRE(out_vector == exp_vector);
}

TEST_CASE("test_reflect_point_by_scaling", "scale")
{
    // GIVEN: A vector and a scaling matrix
    // WHEN: That vector is multiplied by the scaling matrix where the 
    // x-component is multiplied by -1.0
    // THEN: The vector becomes reflected
    Tuple p1 = create_point(2, 3, 4);
    Matrix scale_mat = scale(-1, 1, 1);
    Tuple exp_point = create_point(-2, 3, 4);

    Tuple out_point = scale_mat * p1;

    REQUIRE(out_point == exp_point);
}

TEST_CASE("test_reflect_point_by_reflect", "scale")
{
    // GIVEN: A vector and a reflection matrix
    // WHEN: That vector is multiplied by the reflection matrix 
    // THEN: The vector becomes reflected
    Tuple p1 = create_point(2, 3, 4);
    Matrix reflect_mat = reflect(1, 1, 1);
    Tuple exp_point = create_point(-2, 3, 4);

    Tuple out_point = reflect_mat * p1;

    REQUIRE(out_point == exp_point);
}

// ======== ROTATE ======== // 
TEST_CASE("test_rotate_x", "rotate")
{
    // GIVEN: A point and a rotation matrix
    // AND half_quarter <- rotation_x( pi / 4)
    // AND full_quarter <- rotation_x( pi / 2)
    // WHEN: That point is multiplied by the each of the two rotation matricies 
    // THEN: The point becomes the point becomes rotated by a half_quarter or
    // full quarter respectively.

    Tuple p1 = create_point(0, 1, 0);
    Matrix half_quarter = rotate_x(M_PI / 4);
    Matrix full_quarter = rotate_x(M_PI / 2);

    Tuple exp_half_quarter_point = create_point(0, std::sqrt(2.0) / 2, std::sqrt(2.0) / 2);
    Tuple exp_full_quarter_point = create_point(0, 0, 1);

    Tuple half_quarter_point = half_quarter * p1;
    Tuple full_quarter_point = full_quarter * p1;

    REQUIRE(half_quarter_point == exp_half_quarter_point);
    REQUIRE(full_quarter_point == exp_full_quarter_point);
}

TEST_CASE("test_rotate_x_inverse", "rotate")
{
    // GIVEN: A point and a half-quarter rotation matrix
    // WHEN: That point is multiplied by the inverse of the rotation matrix 
    // THEN: The point becomes reflected

    Tuple p1 = create_point(0, 1, 0);
    Matrix half_quarter = rotate_x(M_PI / 4);
    Matrix inv_half_quarter = half_quarter.inverse();

    Tuple exp_half_quarter_point = create_point(0, std::sqrt(2.0) / 2, -std::sqrt(2.0) / 2);

    Tuple half_quarter_point = inv_half_quarter * p1;

    REQUIRE(half_quarter_point == exp_half_quarter_point);
}

TEST_CASE("test_rotate_y", "rotate")
{
    // GIVEN: A point and a rotation matrix
    // AND half_quarter <- rotation_y( pi / 4)
    // AND full_quarter <- rotation_y( pi / 2)
    // WHEN: That point is multiplied by the each of the two rotation matricies 
    // THEN: The point becomes the point becomes rotated by a half_quarter or
    // full quarter respectively.

    Tuple p1 = create_point(0, 0, 1);
    Matrix half_quarter = rotate_y(M_PI / 4);
    Matrix full_quarter = rotate_y(M_PI / 2);
    Tuple exp_half_quarter_point = create_point(std::sqrt(2.0) / 2, 0, std::sqrt(2.0) / 2);
    Tuple exp_full_quarter_point = create_point(1, 0, 0);

    Tuple half_quarter_point = half_quarter * p1;
    Tuple full_quarter_point = full_quarter * p1;

    REQUIRE(half_quarter_point == exp_half_quarter_point);
    REQUIRE(full_quarter_point == exp_full_quarter_point);
}

TEST_CASE("test_rotate_z", "rotate")
{
    // GIVEN: A point and a rotation matrix
    // AND half_quarter <- rotation_z( pi / 4)
    // AND full_quarter <- rotation_z( pi / 2)
    // WHEN: That point is multiplied by the each of the two rotation matricies 
    // THEN: The point becomes the point becomes rotated by a half_quarter or
    // full quarter respectively.

    Tuple p1 = create_point(0, 1, 0);
    Matrix half_quarter = rotate_z(M_PI / 4);
    Matrix full_quarter = rotate_z(M_PI / 2);
    Tuple exp_half_quarter_point = create_point(-std::sqrt(2.0) / 2, std::sqrt(2.0) / 2, 0);
    Tuple exp_full_quarter_point = create_point(-1, 0, 0);

    Tuple half_quarter_point = half_quarter * p1;
    Tuple full_quarter_point = full_quarter * p1;

    REQUIRE(half_quarter_point == exp_half_quarter_point);
    REQUIRE(full_quarter_point == exp_full_quarter_point);
}
