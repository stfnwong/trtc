/*
 * INTERSECTION
 */

#include <sstream>
#include "Intersection.hpp"

Intersection::Intersection() : target(nullptr), t(0.0) {} 

Intersection::Intersection(std::shared_ptr<Shape> target, float t) : target(std::move(target)), t(t) {} 

std::string Intersection::toString(void) const 
{
    std::ostringstream oss;

    oss << this->target->toString() << " " << "t: " << this->t << std::endl;

    return oss.str();
}




// TODO: later
// TODO; change over to use generic shape
// ======== INTERSECTIONS ======== //
//Intersection Intersect(const Sphere& sphere, const Ray& ray)
//{
//    // TODO : in this implementation the sphere is always a unit sphere 
//    // centered at (0,0,0)
//    Tuple oc = ray.origin - sphere.center;
//    oc.toVector();
//
//    float a    = dot(ray.direction, ray.direction);
//    float b    = 2.0 * dot(ray.direction, oc);
//    float c    = dot(oc, oc) - (sphere.radius * sphere.radius);
//    float disc = (b * b) - (4*a*c);
//
//    if(disc < 0.0)  // no hits
//        return std::vector<float>{};
//
//    float t0 = (-b - std::sqrt(disc)) / (2.0 * a);
//    float t1 = (-b + std::sqrt(disc)) / (2.0 * a);
//
//    return std::vector<float>{t0, t1};
//}
