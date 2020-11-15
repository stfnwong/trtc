/*
 * CANVAS
 */

#include "Canvas.hpp"


Canvas::Canvas(unsigned int height, unsigned int width) : h(height), w(width)
{
    this->init_cdata();
}

/*
 * init_cdata()
 */
void Canvas::init_cdata(void)
{
    this->cdata.reserve(this->h * this->w);
    for(unsigned int y = 0; y < this->h; ++y)
    {
        for(unsigned int x = 0; x < this->w; ++x)
        {
            this->cdata[this->xy_to_pos(x, y)] = Color();
        }
    }
}

/*
 * xy_to_pos()
 */
unsigned int Canvas::xy_to_pos(unsigned int x, unsigned int y) const
{
    return (y * this->h) + x;
}


/*
 * set()
 */
void Canvas::set(unsigned int x, unsigned int y, const Color& c)
{
    this->cdata[this->xy_to_pos(x,y)] = c;
}
/*
 * get()
 */
Color Canvas::get(unsigned int x, unsigned int y) const
{
    return this->cdata[this->xy_to_pos(x, y)];
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
