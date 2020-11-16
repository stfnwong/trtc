/*
 * CANVAS
 */

#ifndef __CANVAS_HPP
#define __CANVAS_HPP

#include <string>
#include <vector>
#include "Color.hpp"


static unsigned int xy_to_pos(unsigned int x, unsigned int y, unsigned int h, unsigned int w);

/*
 * Holds pixel values for an image
 */
class Canvas
{
    private:
        unsigned int w;
        unsigned int h;
        std::vector<Color> cdata;

    private:
        void init_cdata(void);
        unsigned int xy_to_pos(unsigned int x, unsigned int y) const;
        std::string header_string(void) const;

    public:
        Canvas(unsigned int width, unsigned int height);
        // disable assignment and copy construction for now 
        Canvas(const Canvas& that) = delete;
        Canvas operator=(const Canvas& that) const = delete;

        // comparison 
        bool operator==(const Canvas& that) const;
        bool operator!=(const Canvas& that) const;

        void set(unsigned int w, unsigned int h, const Color& c);
        Color get(unsigned int w, unsigned int h) const;
        unsigned int height(void) const;
        unsigned int width(void) const;
        unsigned int size(void) const;

        void clear(void);        // set all colors to 0 (slow!)
        void save(const std::string& filename) const;
        void load(const std::string& filename);

        std::string toString(void) const;
        std::string toPPMString(void) const;

};


#endif /*__CANVAS_HPP*/
