/*
 * SHAPE
 * Trying to generalise Spheres for Intersection testing 
 */

#ifndef __SHAPE_HPP
#define __SHAPE_HPP

#include <string>

#include "Tuple.hpp"        // consider moving to a datastructures header later

/*
 * Since this appears to be an object-oriented design this
 * thing will be the base class for Shapes
 */
struct Shape
{
    public:
        int id;

    public:
        Shape();
        Shape(int i);

        std::string toString(void) const;
};


/*
 * Generic sphere 
 */
struct Sphere : public Shape
{
    float radius;
    Tuple center;

    public:
        Sphere();
        Sphere(float r, const Tuple& c);
        Sphere(int i, float r, const Tuple& c);

        std::string toString(void) const;
};



#endif /*__SHAPE_HPP*/
