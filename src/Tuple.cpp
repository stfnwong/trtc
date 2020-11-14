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

// Arithmetic and assign
Tuple& Tuple::operator+=(const Tuple& that) 
{
    if(this != &that)
    {
        this->x += that.x;
        this->y += that.y;
        this->z += that.z;
        if(this->w == 0.0 && that.w == 0.0)
            this->w = 0.0;
        else
            this->w += that.w;
    }

    return *this;
}

Tuple& Tuple::operator-=(const Tuple& that)
{
    if(this != &that)
    {
        this->x -= that.x;
        this->y -= that.y;
        this->z -= that.z;
        if(this->w == 0.0 && that.w == 0.0)
            this->w = 0.0;
        else
            this->w -= that.w;
    }

    return *this;
}

// Arithmetic 
Tuple Tuple::operator+(const Tuple& that) const
{
    return Tuple(
            this->x + that.x,
            this->y + that.y,
            this->z + that.z,
            (this->w == 1.0 && that.w == 1.0) ? 1.0 : this->w + that.w
            );
}

Tuple Tuple::operator-(const Tuple& that) const
{
    return Tuple(
            this->x - that.x,
            this->y - that.y,
            this->z - that.z,
            (this->w == 1.0 && that.w == 1.0) ? 1.0 : this->w - that.w
            );
}

/*
 * toString()
 */
std::string Tuple::toString(void) const
{
    std::ostringstream oss;

    oss << "Tuple(";
    oss << this->x << ", ";
    oss << this->y << ", ";
    oss << this->z << ", ";
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
