/*
 * COLOR
 * Stuff for blending colors 
 */

#ifndef __COLOR_HPP
#define __COLOR_HPP

#include <string>



struct Color
{
    float r;
    float g; 
    float b;

    public:
        Color();
        Color(float r_new, float g_new, float b_new);
        Color(const Color& that) = default;
        Color(Color&& that) = default;

        bool operator==(const Color& that) const;
        bool operator!=(const Color& that) const;

        // Arithmetic
        Color operator+(const Color& that) const;
        Color operator+(float c) const;
        Color operator-(const Color& that) const;
        Color operator-(float c) const;

        Color operator*(const Color& that) const;
        Color operator*(float) const;


        std::string toString(void) const;
};


#endif /*__COLOR_HPP*/
