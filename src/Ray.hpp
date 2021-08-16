/*
 * RAY
 */

#ifndef __RAY_HPP
#define __RAY_HPP

#include <string>
#include <vector>
#include "Tuple.hpp"
#include "Shape.hpp"        // TODO: this should not stay here

/*
 * A ray
 */
struct Ray
{
    Tuple origin;           // point
    Tuple direction;        // vector (TODO: make a vector in ctor?)

    public:
        Ray(const Tuple& o, const Tuple& d);

        bool operator==(const Ray& that) const;
        bool operator!=(const Ray& that) const;

        Tuple position(float t) const;

        std::string toString(void) const;
};

std::vector<float> Intersect(const Sphere& s, const Ray& r);


#endif /*__RAY_HPP*/
