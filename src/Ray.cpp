/*
 * RAY
 */

#include <cstdlib>
#include <cmath>
#include "Ray.hpp"
#include <sstream>

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

std::string Ray::toString(void) const
{
    std::ostringstream oss;

    oss << "Ray: "; 
    oss << "Origin(" 
        << this->origin.x << "," 
        << this->origin.y << "," 
        << this->origin.z 
        << ") "; 

    oss << "Direction(" 
        << this->direction.x << "," 
        << this->direction.y << "," 
        << this->direction.z 
        << ")";

    return oss.str();
}

// ======== SPHERE ======== //
Sphere::Sphere() : id(std::rand()), radius(1.0), center(create_point(0, 0, 0)) {}

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


// ======== INTERSECTIONS ======== //
std::vector<float> Intersect(const Sphere& sphere, const Ray& ray)
{
    // TODO : in this implementation the sphere is always a unit sphere 
    // centered at (0,0,0)
    Tuple oc = ray.origin - sphere.center;
    oc.toVector();

    float a    = dot(ray.direction, ray.direction);
    float b    = 2.0 * dot(ray.direction, oc);
    float c    = dot(oc, oc) - (sphere.radius * sphere.radius);
    float disc = (b * b) - (4*a*c);

    if(disc < 0.0)  // no hits
        return std::vector<float>{};

    float t0 = (-b - std::sqrt(disc)) / (2.0 * a);
    float t1 = (-b + std::sqrt(disc)) / (2.0 * a);

    return std::vector<float>{t0, t1};
}
