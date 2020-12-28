/*
 * RAY
 */

#ifndef __RAY_HPP
#define __RAY_HPP

#include "Tuple.hpp"


struct Ray
{
    Tuple origin;           // point
    Tuple direction;        // vector (TODO: make a vector in ctor?)

    public:
        Ray(const Tuple& o, const Tuple& d);

        bool operator==(const Ray& that) const;
        bool operator!=(const Ray& that) const;
};


#endif /*__RAY_HPP*/
