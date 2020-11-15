/*
 * CANVAS
 */

#ifndef __CANVAS_HPP
#define __CANVAS_HPP

#include <string>
#include <vector>
#include "Color.hpp"


class Canvas
{
    private:
        unsigned int h;
        unsigned int w;
        std::vector<Color> cdata;

    private:
        void init_cdata(void);
        unsigned int xy_to_pos(unsigned int x, unsigned int y) const;

    public:
        Canvas(unsigned int height, unsigned int width);

        void set(unsigned int x, unsigned int y, const Color& c);
        Color get(unsigned int x, unsigned int y) const;
        unsigned int height(void) const;
        unsigned int width(void) const;

        void clear(void);        // set all colors to 0 (slow!)

};


#endif /*__CANVAS_HPP*/
