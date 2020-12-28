/*
 * RAY
 */

#include "Ray.hpp"


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
