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

        bool operator<(const Intersection& that) const;

        std::string toString(void) const;
};


// Initially this is just going to be a vector over an Intersection

/*
 * Intersections
 * TODO: needs to be sortable...
 */
struct Intersections
{
    std::vector<Intersection> is;

    public:
        Intersections();
        Intersections(const std::vector<Intersection>& is);
        unsigned int count(void) const;
        void add(const Intersection& ii);

        // Allow array access 
        Intersection  operator[](const unsigned int idx);
        //Intersection& operator[](const unsigned int idx);
};


/*
 * Compute an intersection 
 */
Intersections Intersect(std::shared_ptr<Sphere> sphere, const Ray& ray);
//Intersections Intersect(std::shared_ptr<Shape> shape, const Ray& ray);


#endif /*__INTERSECTION_HPP*/
