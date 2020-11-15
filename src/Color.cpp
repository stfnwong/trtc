/*
 * COLOR
 * Stuff for blending colors 
 */

#include <sstream>
#include <iomanip>

#include "Common.hpp"
#include "Color.hpp"



Color::Color() : r(0.0), g(0.0), b(0.0) {} 

Color::Color(float r_new, float g_new, float b_new) : r(r_new), g(g_new), b(b_new) {} 

// copy ctor 
//Color::Color(const Color& that) : r(that.r), g(that.g), b(that.b) 
//{
//    
//}



bool Color::operator==(const Color& that) const
{
    if(!equal(this->r, that.r))
        return false;
    if(!equal(this->g, that.g))
        return false;
    if(!equal(this->b, that.b))
        return false;

    return true;
}

bool Color::operator!=(const Color& that) const
{
    return !(*this == that);
}


// Arithmetic operators 
Color Color::operator+(const Color& that) const
{
    return Color(
            this->r + that.r,
            this->g + that.g,
            this->b + that.b
            );
}

Color Color::operator+(float c) const
{
    return Color(
            this->r + c,
            this->g + c,
            this->b + c
            );
}

Color Color::operator-(const Color& that) const
{
    return Color(
            this->r - that.r,
            this->g - that.g,
            this->b - that.b
            );
}

Color Color::operator-(float c) const
{
    return Color(
            this->r - c,
            this->g - c,
            this->b - c 
            );
}

Color Color::operator*(const Color& that) const
{
    return Color(
            this->r * that.r,
            this->g * that.g,
            this->b * that.b
            );
}

Color Color::operator*(float c) const
{
    return Color(
            this->r * c,
            this->g * c,
            this->b * c
            );
}

/*
 * Assignment
 */
Color& Color::operator=(const Color& that) 
{
    if(this != & that)
    {
        this->r = that.r;
        this->g = that.g;
        this->b = that.b;
    }
    return *this;
}



/*
 * toString()
 */
std::string Color::toString(void) const
{
    std::ostringstream oss;

    oss << "Color(";
    oss << this->r << ", ";
    oss << this->g << ", ";
    oss << this->b << ")";

    return oss.str();
}

