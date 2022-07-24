// Light sources 

#include <sstream>
#include <iomanip>

#include "Common.hpp"
#include "Light.hpp"


// ======== POINTLIGHT ========  //
PointLight::PointLight(const Tuple& pos, const Color& col) : 
    pos(pos), col(col) {} 

bool PointLight::operator==(const PointLight& that) const
{
    if(this->pos != that.pos)
        return false;
    if(this->col != that.col)
        return false;

    return true;
}

bool PointLight::operator!=(const PointLight& that) const
{
    return !(*this == that);
}

std::string PointLight::toString(void) const
{
    std::ostringstream oss;

    oss << "Pos:   " << this->pos.toString() << std::endl;
    oss << "Color: " << this->col.toString() << std::endl;

    return oss.str();
}
