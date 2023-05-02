/*
 * INTERSECTION
 */

#include <cmath>
#include <sstream>

#include "Common.hpp"
#include "Intersection.hpp"


// ======== INTERSECTION ======== //
Intersection::Intersection() : target(nullptr), t(0.0) {} 

Intersection::Intersection(std::shared_ptr<const Shape> target, float t) : target(std::move(target)), t(t) {} 

bool Intersection::operator<(const Intersection& that) const
{
    return (this->t < that.t);
}

bool Intersection::operator==(const Intersection& that) const
{
    if(this->target != that.target)
        return false;
    if(!equal_eps(this->t, that.t, 1e-6))
        return false;

    return true;
}

bool Intersection::operator!=(const Intersection& that) const
{
    return !(*this == that);
}

float Intersection::distance(void) const
{
    return this->t;
}

std::string Intersection::toString(void) const 
{
    std::ostringstream oss;

    oss << this->target->toString() << " " << "t: " << this->t << std::endl;

    return oss.str();
}


// ======== INTERSECT ======== //
std::vector<Intersection> Intersect(std::shared_ptr<const Sphere> shape, const Ray& ray)
{
    // TODO : in this implementation the shape is always a unit sphere 
    Ray r = ray_transform(ray, shape->transform.inverse());
    // centered at (0,0,0)
    Tuple oc = r.origin - shape->center;
    oc.toVector();

    float a    = dot(r.direction, r.direction);
    float b    = 2.0 * dot(r.direction, oc);
    float c    = dot(oc, oc) - (shape->radius * shape->radius); // TODO: for the time being we are only testing spheres
    float disc = (b * b) - (4*a*c);

    if(disc < 0.0)  // no hits
        return std::vector<Intersection>();

    float t0 = (-b - std::sqrt(disc)) / (2.0 * a);
    float t1 = (-b + std::sqrt(disc)) / (2.0 * a);

    std::vector<Intersection> is = Intersections(
            Intersection(shape, t0),
            Intersection(shape, t1)
    );

    return is;
}


Intersection Hit(const std::vector<Intersection>& intersections)
{
    for(const auto& intersect : intersections)
    {
        if(intersect.distance() > 0.0f)
            return intersect;
    }

    return Intersection();          // nothing in front of camera
}
