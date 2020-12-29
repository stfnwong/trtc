/*
 * RAY
 */

#include <cstdlib>
#include <cmath>
#include "Ray.hpp"


// ======== RAY ======== //

Ray::Ray(const Tuple& o, const Tuple& d) : origin(o), direction(d) {} 

bool Ray::operator==(const Ray& that) const
{
    if(this->origin != that.origin)
        return false;
    if(this->direction != that.direction)
        return false;

    return true;
}

bool Ray::operator!=(const Ray& that) const
{
    return !(*this == that);
}


Tuple Ray::position(float t) const
{
    return this->origin + this->direction * t;
}

// ======== SPHERE ======== //
Sphere::Sphere() : id(std::rand()), radius(1.0), center(create_point(0, 0, 0)) {}

// ======== INTERSECTIONS ======== //
std::vector<float> Intersect(const Sphere& sphere, const Ray& ray)
{
    // TODO : in this implementation the sphere is always a unit sphere 
    // centered at (0,0,0)

    Tuple oc = ray.origin - sphere.center;

    float a    = dot(ray.direction, ray.direction);
    float b    = 2.0 * dot(oc, ray.direction);
    float c    = dot(oc, oc) - (sphere.radius * sphere.radius);
    float disc = (b * b) - (4*a*c);

    if(disc < 0.0)  // no hits
        return std::vector<float>{};

    float t0 = (-b - std::sqrt(disc)) / (2.0 * a);
    float t1 = (-b + std::sqrt(disc)) / (2.0 * a);

    return std::vector<float>{t0, t1};

}
