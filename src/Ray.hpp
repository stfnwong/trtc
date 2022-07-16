/*
 * RAY
 */

#ifndef __RAY_HPP
#define __RAY_HPP

#include <string>
#include <vector>

#include "Matrix.hpp"
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
        //Ray   transformed(const Matrix& t) const;
        //void  transform(const Matrix& t);

        std::string toString(void) const;
};

// TODO: probably won't keep this here....
Ray ray_transform(const Ray& ray, const Matrix& transform);


#endif /*__RAY_HPP*/
