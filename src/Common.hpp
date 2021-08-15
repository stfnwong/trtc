/*
 * COMMON
 * Stuff that gets used often
 */

#ifndef __COMMON_HPP
#define __COMMON_HPP

#include <cmath>

// Matrix multiply is not accurate to 1e-6 with current algorithm
#define COMP_EPSILON 1e-5   


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
