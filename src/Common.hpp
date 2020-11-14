/*
 * COMMON
 * Stuff that gets used often
 */

#ifndef __COMMON_HPP
#define __COMMON_HPP

#include <cmath>

#define COMP_EPSILON 1e-5


inline bool equal(float a, float b)
{
    return (std::fabs(a - b) < COMP_EPSILON) ? true : false;
}


#endif /*__COMMON_HPP*/
