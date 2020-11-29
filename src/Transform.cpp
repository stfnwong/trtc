/*
 * TRANSFORM
 * Matrix tranforms 
 *
 */

#include <iostream>
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
