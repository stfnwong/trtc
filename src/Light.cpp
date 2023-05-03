// Light sources 

#include <cmath>
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


Color lighting(const Material& mat, const PointLight& light, const Tuple& pos, const Tuple& eyev, const Tuple& normalv)
{
    Color ecolor = mat.col * light.col;  // "effective" color
    Tuple lightv = normalize(light.pos - pos);

    // Ambient contribution
    Color ambient = ecolor * mat.ambient;

    // light_dot_normal represents the cosine of the angle between the light vector
    // and the normal vector. A negative number means that the light is on the other 
    // side of the surface.
    Color diffuse;
    Color specular;

    float light_dot_normal = dot(lightv, normalv);
    if(light_dot_normal < 0)
    {
        diffuse = Color(0, 0, 0);
        specular = Color(0, 0, 0);
    }
    else
    {
        diffuse = ecolor * mat.diffuse * light_dot_normal;

        // reflect_dot_eye represents the consine of the angle between the reflection 
        // vector and the eye vector. A negative number means the light reflects away
        // from the eye.
        Tuple reflectv = reflect(-lightv, normalv);
        float reflect_dot_eye = dot(reflectv, eyev);
        
        if(reflect_dot_eye <= 0.0)
            specular = Color(0,0,0);
        else
        {
            // Compute the specular contribution
            float factor = std::pow(reflect_dot_eye, mat.shininess);
            specular = light.col * mat.specular * factor;
        }
    }
            
    return ambient + diffuse + specular;
}
