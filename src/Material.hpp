#ifndef __MATERIAL_HPP
#define __MATERIAL_HPP

#include <string>
#include "Color.hpp"

struct Material
{
    Color col;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    public:
        Material();
        Material(const Color& col, float a, float d, float sp, float sh);

        bool operator==(const Material& that) const;
        bool operator!=(const Material& that) const;

        std::string toString(void) const;
};


#endif /*__MATERIAL_HPP*/
