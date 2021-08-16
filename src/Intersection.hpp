/*
 * INTERSECTION
 */

#ifndef __INTERSECTION_HPP
#define __INTERSECTION_HPP

#include <memory>
#include <string>
#include <vector>

#include "Ray.hpp"
#include "Shape.hpp"


struct Intersection
{
    std::shared_ptr<Shape> target;    
    float t;

    public:
        Intersection();
        Intersection(std::shared_ptr<Shape> shape, float t);

        std::string toString(void) const;
};


// TODO: later
//Intersection Intersect(const Shape& shape, const Ray& ray);


#endif /*__INTERSECTION_HPP*/
