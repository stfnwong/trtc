// Light sources 


#ifndef __LIGHT_HPP
#define __LIGHT_HPP

#include <string>

#include "Color.hpp"
#include "Tuple.hpp"




struct PointLight
{
    Tuple pos;
    Color col;

    public:
        PointLight(const Tuple& pos, const Color& intensity);

        bool operator==(const PointLight& that) const;
        bool operator!=(const PointLight& that) const;

        std::string toString(void) const;

};

#endif /*__LIGHT_HPP*/
