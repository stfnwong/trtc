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
TEST_CASE("test_translate", "transform")
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

TEST_CASE("test_translate_inverse", "transform")
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

TEST_CASE("test_translate_does_not_affect_vectors", "transform")
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
TEST_CASE("test_scale_point", "transform")
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

TEST_CASE("test_scale_vector", "transform")
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

TEST_CASE("test_scale_vector_inverse", "transform")
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

TEST_CASE("test_reflect_point_by_scaling", "transform")
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

TEST_CASE("test_reflect_point_by_reflect", "transform")
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
