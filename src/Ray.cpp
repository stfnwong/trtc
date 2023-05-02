/*
 * RAY
 */

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

/*
 * Transform a Ray
 */
Ray ray_transform(const Ray& ray, const Matrix& transform) 
{
     return Ray(transform * ray.origin, transform * ray.direction);
}
