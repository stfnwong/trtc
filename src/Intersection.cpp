/*
 * INTERSECTION
 */

#include <sstream>
#include "Intersection.hpp"


// ======== INTERSECTION ======== //
Intersection::Intersection() : target(nullptr), t(0.0) {} 

Intersection::Intersection(std::shared_ptr<Shape> target, float t) : target(std::move(target)), t(t) {} 

std::string Intersection::toString(void) const 
{
    std::ostringstream oss;

    oss << this->target->toString() << " " << "t: " << this->t << std::endl;

    return oss.str();
}



// ======== INTERSECTIONS ======== //
Intersections::Intersections() : is(std::vector<Intersection>()) {} 

Intersections::Intersections(const std::vector<Intersection>& is) : is(is) {} 

unsigned int Intersections::count(void) const
{
    return this->is.size();
}

Intersection Intersections::operator[](const unsigned int idx) 
{
    return this->is[idx];
}

//Intersection& Intersections::operator[](const unsigned int idx) 
//{
//    return this->is[idx];
//}





// TODO; change over to use generic shape
// ======== INTERSECTIONS ======== //
Intersections Intersect(const Shape& shape, const Ray& ray)
{
    // TODO : in this implementation the shape is always a unit sphere 
    // centered at (0,0,0)
    Tuple oc = ray.origin - shape.center;
    oc.toVector();

    float a    = dot(ray.direction, ray.direction);
    float b    = 2.0 * dot(ray.direction, oc);
    float c    = dot(oc, oc) - (shape.radius * shape.radius); // TODO: for the time being we are only testing spheres
    float disc = (b * b) - (4*a*c);

    if(disc < 0.0)  // no hits
        return std::vector<float>{};

    float t0 = (-b - std::sqrt(disc)) / (2.0 * a);
    float t1 = (-b + std::sqrt(disc)) / (2.0 * a);

    return std::vector<float>{t0, t1};
}

