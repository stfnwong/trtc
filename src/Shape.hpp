/*
 * SHAPE
 * Trying to generalise Spheres for Intersection testing 
 */

#ifndef __SHAPE_HPP
#define __SHAPE_HPP

#include <string>

#include "Matrix.hpp"
#include "Tuple.hpp"        // consider moving to a datastructures header later
#include "Material.hpp"

/*
 * Since this appears to be an object-oriented design this
 * thing will be the base class for Shapes
 */
struct Shape
{
    public:
        int id;
        Matrix transform;

    public:
        Shape();
        Shape(int i);
        Shape(int i, const Matrix& t);

        std::string toString(void) const;
};


/*
 * Generic sphere 
 */
struct Sphere : public Shape
{
    float radius;
    Tuple center;
    Material mat;

    public:
        Sphere();
        Sphere(float r, const Tuple& c);
        Sphere(int i, float r, const Tuple& c);
        Sphere(int i, float r, const Tuple& c, const Material& mat);

        void set_transform(const Matrix& t);
        void set_material(const Material& m);
        Tuple normal_at(const Tuple& p);

        std::string toString(void) const;
};



#endif /*__SHAPE_HPP*/
