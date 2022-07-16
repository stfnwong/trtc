/*
 * SHAPE
 * Trying to generalise Spheres for Intersection testing 
 */

#include <cstdlib>
#include <sstream>

#include "Shape.hpp"


// ======== SHAPE ======== //
Shape::Shape() : id(std::rand()), transform(eye(4)) {} 

Shape::Shape(int i) : id(i), transform(eye(4)) {} 

Shape::Shape(int i, const Matrix& t) : id(i), transform(t) {} 

std::string Shape::toString(void) const
{
    std::ostringstream oss;

    //oss << "Shape(" << unsigned(this->id) << ")";         // <- TODO : segfault here with shared_ptr<Shape>
    oss << "Shape()" << std::endl;

    return oss.str();
}


// ======== SPHERE ======== //
Sphere::Sphere() : Shape(std::rand()), radius(1.0), center(create_point(0, 0, 0)) {}
//Sphere::Sphere() : id(std::rand()), radius(1.0), center(create_point(0, 0, 0)) {}

Sphere::Sphere(float r, const Tuple& c) : Shape{ std::rand() }, radius(r), center(c) {}

Sphere::Sphere(int i, float r, const Tuple& c) : Shape{ i }, radius(r), center(c) {}

void Sphere::set_transform(const Matrix& t)
{
    this->transform = t;
}

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

