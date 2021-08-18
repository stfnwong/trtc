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

/*
 * Intersection
 */
struct Intersection
{
    std::shared_ptr<Shape> target;    
    float t;

    public:
        Intersection();
        Intersection(std::shared_ptr<Shape> shape, float t);

        std::string toString(void) const;
};


// Initially this is just going to be a vector over an Intersection

/*
 * Intersections
 */
struct Intersections
{
    std::vector<Intersection> is;

    public:
        Intersections();
        Intersections(const std::vector<Intersection>& is);
        unsigned int count(void) const;

        // Allow array access 
        Intersection  operator[](const unsigned int idx);
        //Intersection& operator[](const unsigned int idx);
};

Intersections Intersect(const Shape& shape, const Ray& ray);

//Intersection Hit(const std::vector<Intersection>& is);


#endif /*__INTERSECTION_HPP*/
