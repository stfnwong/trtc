/*
 * INTERSECTION
 */

#include <cmath>
#include <sstream>
#include "Intersection.hpp"


// ======== INTERSECTION ======== //
Intersection::Intersection() : target(nullptr), t(0.0) {} 

Intersection::Intersection(std::shared_ptr<Shape> target, float t) : target(std::move(target)), t(t) {} 

bool Intersection::operator<(const Intersection& that) const
{
    return (this->t < that.t);
}

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

void Intersections::add(const Intersection& ii)
{
    this->is.push_back(ii);
}

Intersection Intersections::operator[](const unsigned int idx) 
{
    return this->is[idx];
}

//Intersection& Intersections::operator[](const unsigned int idx) 
//{
//    return this->is[idx];
//}





// ======== INTERSECTIONS ======== //
Intersections Intersect(std::shared_ptr<Sphere> shape, const Ray& ray)
{
    // TODO : in this implementation the shape is always a unit sphere 
    // centered at (0,0,0)
    Tuple oc = ray.origin - shape->center;
    oc.toVector();

    float a    = dot(ray.direction, ray.direction);
    float b    = 2.0 * dot(ray.direction, oc);
    float c    = dot(oc, oc) - (shape->radius * shape->radius); // TODO: for the time being we are only testing spheres
    float disc = (b * b) - (4*a*c);

    if(disc < 0.0)  // no hits
        return Intersections();

    float t0 = (-b - std::sqrt(disc)) / (2.0 * a);
    float t1 = (-b + std::sqrt(disc)) / (2.0 * a);

    Intersections isections;

    isections.add(Intersection(shape, t0));
    isections.add(Intersection(shape, t1));

    return isections;
}
