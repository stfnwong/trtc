
#include <iomanip>
#include <sstream>

#include "Common.hpp"
#include "Material.hpp"



Material::Material() 
{
    this->col = Color(1, 1, 1);     // this is actually a bizzare default color (bright white)
    this->ambient = 0.1;
    this->diffuse = 0.9;
    this->specular = 0.9;
    this->shininess = 200.0;
}

Material::Material(const Color& col, float a, float d, float sp, float sh) :
    col(col), ambient(a), diffuse(d), specular(sp), shininess(sh) {}


bool Material::operator==(const Material& that) const
{
    if(!equal(this->ambient, that.ambient))
        return false;
    if(!equal(this->diffuse, that.diffuse))
        return false;
    if(!equal(this->specular, that.specular))
        return false;
    if(!equal(this->shininess, that.shininess))
        return false;

    return true;
}

bool Material::operator!=(const Material& that) const
{
    return !(*this == that);
}

std::string Material::toString(void) const
{
    std::ostringstream oss;

    return oss.str();
}
