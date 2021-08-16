/*
 * SHAPE
 * Trying to generalise Spheres for Intersection testing 
 */

#include <cstdlib>
#include <sstream>

#include "Shape.hpp"


// ======== SHAPE ======== //
Shape::Shape() : id(std::rand()) {} 

Shape::Shape(int i) : id(i) {} 

std::string Shape::toString(void) const
{
    std::ostringstream oss;

    oss << "Shape(" << this->id << ")";

    return oss.str();
}


// ======== SPHERE ======== //
Sphere::Sphere() : radius(1.0), center(create_point(0, 0, 0)) {}
//Sphere::Sphere() : id(std::rand()), radius(1.0), center(create_point(0, 0, 0)) {}

Sphere::Sphere(float r, const Tuple& c) : Shape{ std::rand() }, radius(r), center(c) {}

Sphere::Sphere(int i, float r, const Tuple& c) : Shape{ i }, radius(r), center(c) {}
//Sphere::Sphere(int i, float r, const Tuple& c) : id(i), radius(r), center(c) {}

std::string Sphere::toString(void) const
{
    std::ostringstream oss;

    oss << "Sphere(" 
        << this->center.x << ","
        << this->center.y << ","
        << this->center.z << ", r " 
        << this->radius << ")";

    return oss.str();
}

