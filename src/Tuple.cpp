/*
 * TUPLE
 * A ordered set of numbers 
 */

#include <cmath>
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

// unary minus (negation)
Tuple Tuple::operator-(void) const
{
    return Tuple(
            -this->x,
            -this->y,
            -this->z,
            this->w
            );
}

// Arithmetic 
Tuple Tuple::operator+(const Tuple& that) const
{
    return Tuple(
            this->x + that.x,
            this->y + that.y,
            this->z + that.z,
            std::fmin(1.0, this->w + that.w)
            );
}

Tuple Tuple::operator-(const Tuple& that) const
{
    return Tuple(
            this->x - that.x,
            this->y - that.y,
            this->z - that.z,
            (this->w == that.w) ? this->w : this->w - that.w
            );
}

/*
 * scalar multiply
 */
Tuple Tuple::operator*(float that) const
{
    return Tuple(
            this->x * that,
            this->y * that,
            this->z * that,
            this->w
            );
}

Tuple Tuple::operator/(float that) const
{
    return Tuple(
            this->x / that,
            this->y / that,
            this->z / that,
            this->w
            );
}

/*
 * Products
 */
float Tuple::dot(const Tuple& that) const
{
    return (this->x * that.x) +
           (this->y * that.y) + 
           (this->z * that.z) + 
           (this->w * that.w);
}
/*
 * cross()
 */
Tuple Tuple::cross(const Tuple& that) const
{
    return Tuple(
            this->y * that.z - this->z * that.y,
            this->z * that.x - this->x * that.z,
            this->x * that.y - this->y * that.x,
            0.0
            );
}

/*
 * mag()
 */
float Tuple::mag(void) const
{
    return std::sqrtf(
            this->x * this->x + 
            this->y * this->y +
            this->z * this->z
            );
}

/*
 * norm()
 */
Tuple Tuple::norm(void) const
{
    float len = this->mag();
    return Tuple(
            this->x / len,
            this->y / len,
            this->z / len,
            this->w
            );
}

/*
 * point()
 */
bool Tuple::point(void) const
{
    return this->w == 1.0 ? true : false;
}

/*
 * vector()
 */
bool Tuple::vector(void) const
{
    return this->w == 0.0 ? true : false;
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
    return Tuple(x, y, z, 0.0);
}

Tuple create_point(float x, float y, float z)
{
    return Tuple(x, y, z, 1.0);
}



float dot(const Tuple& a, const Tuple& b)
{
    return a.dot(b);
}

Tuple cross(const Tuple& a, const Tuple& b)
{
    return a.cross(b);
}
