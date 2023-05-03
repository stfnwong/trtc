/*
 * COLOR
 * Stuff for blending colors 
 */

#ifndef __COLOR_HPP
#define __COLOR_HPP

#include <algorithm>
#include <string>


/*
 * col_to_byte()
 * We clip to scale-1 here so that the output wraps at 255 for bytes
 */
inline int col_to_byte(float col, int scale)
{
    return (float(col * scale) < scale) ? std::max(0, int(col * scale)) : scale-1;
}


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

        // TODO ; copy assignment operator

        bool operator==(const Color& that) const;
        bool operator!=(const Color& that) const;

        // Arithmetic
        Color operator+(const Color& that) const;
        Color operator+(float c) const;
        Color operator-(const Color& that) const;
        Color operator-(float c) const;

        Color operator*(const Color& that) const;
        Color operator*(float c) const;

        // Assignment
        Color& operator=(const Color& that);

        std::string to8bppString(void) const;
        std::string toString(void) const;
};


#endif /*__COLOR_HPP*/
