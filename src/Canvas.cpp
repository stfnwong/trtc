/*
 * CANVAS
 */

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Canvas.hpp"

/*
 * Generic xy -> idx function
 */
static unsigned int xy_to_pos(unsigned int x, unsigned int y, unsigned int h, unsigned int w)
{
    return (y * h) + ((x % w == 0) ? 0 : x);
}

/*
 * ================ CANVAS ================ 
 */
Canvas::Canvas(unsigned int width, unsigned int height) : w(width), h(height)
{
    this->init_cdata();
}

/*
 * init_cdata()
 */
void Canvas::init_cdata(void)
{
    this->cdata.reserve(this->h * this->w);
    for(unsigned int pix = 0; pix < (this->h * this->w); ++pix)
        this->cdata[pix] = Color();
}

/*
 * xy_to_pos()
 */
unsigned int Canvas::xy_to_pos(unsigned int x, unsigned int y) const
{
    return (y * this->h) + x;
}

/*
 * headerString()
 */
std::string Canvas::header_string(void) const
{
    std::ostringstream oss;

    oss << "P3\n" << this->w << " " << this->h << "\n";
    oss << "255\n";

    return oss.str();
}

/*
 * Comparison
 * (slow)
 */
bool Canvas::operator==(const Canvas& that) const
{
    if(this->h != that.h)
        return false;
    if(this->w != that.w)
        return false;
    for(unsigned int pix = 0; pix < (this->h * this->w); ++pix)
    {
        if(this->cdata[pix] != that.cdata[pix])
            return false;
    }

    return true;
}

bool Canvas::operator!=(const Canvas& that) const
{
    return !(*this == that);
}


/*
 * set()
 */
void Canvas::set(unsigned int w, unsigned int h, const Color& c)
{
    this->cdata[this->xy_to_pos(h, w)] = c;
}
/*
 * get()
 * NOTE: returns a copy
 */
Color Canvas::get(unsigned int w, unsigned int h) const
{
    return this->cdata[this->xy_to_pos(h, w)];
}

/*
 * height()
 */
unsigned int Canvas::height(void) const
{
    return this->h;
}
/*
 * width()
 */
unsigned int Canvas::width(void) const
{
    return this->w;
}
/*
 * size()
 */
unsigned int Canvas::size(void) const
{
    return this->w * this->h;
}

/*
 * clear()
 */
void Canvas::clear(void) 
{
    for(unsigned int y = 0; y < this->h; ++y)
    {
        for(unsigned int x = 0; x < this->w; ++x)
        {
            this->cdata[this->xy_to_pos(x, y)] = Color();
        }
    }
}

/*
 * ================ File handling ================
 */
/*
 * save()
 */
void Canvas::save(const std::string& filename) const
{
    std::ofstream outfile;

    try {
        outfile.open(filename);
    }
    catch(std::ios_base::failure& e) {
        std::cerr << "[" << __func__ << "] " << e.what() << std::endl;
        return;
    }

    // header
    outfile << "P3\n" << this->w << " " << this->h << "255\n" << std::endl;
    // pixel data
    for(unsigned int pixel = 0; pixel < this->size(); ++pixel)
    {
        if(pixel > 0 && ((pixel % this->w) == 0))
            outfile << std::endl;
        outfile << this->cdata[pixel].to8bppString() << " ";
    }
    outfile << std::endl;
    outfile.close();
}

/*
 * load()
 */
void Canvas::load(const std::string& filename)
{
    std::ifstream infile;

    try {
        infile.open(filename);
    }
    catch(std::ios_base::failure& e) {
        std::cerr << "[" << __func__ << "] " << e.what() << std::endl;
        return;
    }

    // read header

    
}


/*
 * toString()
 */
std::string Canvas::toString(void) const
{
    std::ostringstream oss;

    oss << "Canvas h: " << std::dec << this->h << ", w: " << std::dec << this->w;

    return oss.str();
}

/*
 * toPPMString()
 */
std::string Canvas::toPPMString(void) const
{
    std::ostringstream oss;

    oss << this->header_string() << std::endl;

    for(unsigned int pixel = 0; pixel < this->size(); ++pixel)
    {
        if(pixel > 0 && ((pixel % this->w) == 0))
            oss << std::endl;
        oss << this->cdata[pixel].to8bppString() << " ";
    }
    oss << std::endl;

    return oss.str();
}
