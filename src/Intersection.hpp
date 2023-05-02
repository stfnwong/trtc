/*
 * INTERSECTION
 */

#ifndef __INTERSECTION_HPP
#define __INTERSECTION_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "Ray.hpp"
#include "Shape.hpp"

/*
 * Intersection
 */
struct Intersection
{
    std::shared_ptr<const Shape> target;    
    float t;

    public:
        Intersection();
        Intersection(std::shared_ptr<const Shape> shape, float t);

        bool operator<(const Intersection& that) const;
        bool operator==(const Intersection& that) const;
        bool operator!=(const Intersection& that) const;

        float distance(void) const;

        std::string toString(void) const;
};


// Create an intersection vector out of a collection of intersections
template <typename ...Args> std::vector<Intersection> Intersections(const Args&... args)
{
    std::vector<Intersection> is{ args... };
    std::sort(is.begin(), is.end());
    return  is;
}

/*
 * Compute an intersection 
 */
std::vector<Intersection> Intersect(std::shared_ptr<const Sphere> sphere, const Ray& ray);

Intersection Hit(const std::vector<Intersection>& intersections);

#endif /*__INTERSECTION_HPP*/
