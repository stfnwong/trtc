/*
 * TUPLE
 * A ordered set of numbers 
 */


#include <sstream>
#include "Common.hpp"
#include "Tuple.hpp"

/*
 * Tuple Constructors
 */
Tuple::Tuple() : x(0.0), y(0.0), z(0.0), w(0.0) {} 

Tuple::Tuple(float x_new, float y_new, float z_new) : x(x_new), y(y_new), z(z_new), w(0.0) {} 

Tuple::Tuple(float x_new, float y_new, float z_new, float w_new) : x(x_new), y(y_new), z(z_new), w(w_new) {} 


// operators
/*
 * ==
 */
bool Tuple::operator==(const Tuple& that) const
{
    if(!equal(this->x, that.x))
        return false;
    if(!equal(this->y, that.y))
        return false;
    if(!equal(this->z, that.z))
        return false;
    if(!equal(this->w, that.w))
        return false;

    return true;
}

/*
 * !=
 */
bool Tuple::operator!=(const Tuple& that) const
{
    return !(*this == that);
}

/*
 * toString()
 */
std::string Tuple::toString(void) const
{
    std::ostringstream oss;

    oss << "Tuple(";
    oss << this->x << ",";
    oss << this->y << ",";
    oss << this->z << ",";
    oss << this->w << ")";

    return oss.str();
}


/*
 * Factories
 */

Tuple create_vector(float x, float y, float z)
{
    return Tuple(x, y, z, 1.0);
}

Tuple create_point(float x, float y, float z)
{
    return Tuple(x, y, z, 0.0);
}
