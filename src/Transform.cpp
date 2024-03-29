/*
 * TRANSFORM
 * Matrix tranforms 
 *
 */

#include <cmath>
#include "Transform.hpp"


/*
 * translate()
 */
Matrix translate(float x, float y, float z)
{
    Matrix t = eye(4);

    t(0,3) = x;
    t(1,3) = y;
    t(2,3) = z;

    return t;
}

/*
 * scale()
 */
Matrix scale(float x, float y, float z)
{
    Matrix s = eye(4);

    s(0,0) = x;
    s(1,1) = y;
    s(2,2) = z;
    s(3,3) = 1.0f;

    return s;
}

/*
 * reflect()
 */
Matrix reflect(float x, float y, float z)
{
    Matrix r = eye(4);

    r(0,0) = -x;
    r(1,1) = y;
    r(2,2) = z;

    return r;
}

// ======== ROTATIONS ======== //
/*
 * rotate_x()
 */
Matrix rotate_x(float angle)
{
    Matrix r = eye(4);

    r(1, 1) = std::cos(angle);
    r(1, 2) = std::sin(-angle);
    r(2, 1) = std::sin(angle);
    r(2, 2) = std::cos(angle);

    return r;
}

/*
 * rotate_y()
 */
Matrix rotate_y(float angle)
{
    Matrix r = eye(4);

    r(0, 0) = std::cos(angle);
    r(2, 0) = std::sin(-angle);
    r(0, 2) = std::sin(angle);
    r(2, 2) = std::cos(angle);

    return r;
}

/*
 * rotate_z()
 */
Matrix rotate_z(float angle)
{
    Matrix r = eye(4);

    r(0, 0) = std::cos(angle);
    r(0, 1) = std::sin(-angle);
    r(1, 0) = std::sin(angle);
    r(1, 1) = std::cos(angle);

    return r;
}


// ======== SHEAR ======== //
/*
 * shear()
 */
Matrix shear(float xy, float xz, float yx, float yz, float zx, float zy)
{
    Matrix s = eye(4);

    s(0, 1) = xy;
    s(0, 2) = xz;
    s(1, 0) = yx;
    s(1, 2) = yz;
    s(2, 0) = zx;
    s(2, 1) = zy;

    return s;
}
