/*
 * COMMON
 * Stuff that gets used often
 */

#ifndef __COMMON_HPP
#define __COMMON_HPP

#include <cmath>

#define COMP_EPSILON 1e-6


inline bool equal(float a, float b)
{
    return (std::fabs(a - b) < COMP_EPSILON) ? true : false;
}

//inline float fmin(float a, float b)
//{
//    return (a < b) ? a : b;
//}
//
//inline float fmax(float a, float b)
//{
//    return (a < b) ? b : a;
//}


#endif /*__COMMON_HPP*/
