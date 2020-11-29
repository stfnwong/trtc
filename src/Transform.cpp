/*
 * TRANSFORM
 * Matrix tranforms 
 *
 */

#include <iostream>
#include "Transform.hpp"



Matrix translate(float x, float y, float z)
{
    Matrix t = eye(4);

    t(0,3) = x;
    t(1,3) = y;
    t(2,3) = z;

    return t;
}
