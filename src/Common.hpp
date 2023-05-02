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

// Test where something is equal to within eps 
inline bool equal_eps(float a, float b, float eps)
{
    return (std::fabs(a - b) < eps) ? true : false;
}

#endif /*__COMMON_HPP*/
