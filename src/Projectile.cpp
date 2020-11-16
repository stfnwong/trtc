/*
 * PROJECTILE
 * This is just a little test of the vector and point implementation
 */

#include <sstream>
#include <utility>
#include "Projectile.hpp"


/*
 * ================ PROJECTILE ================ 
 */
Projectile::Projectile() : position(Tuple()), velocity(Tuple())
{
    this->position.toPoint();
    this->velocity.toVector();
}

Projectile::Projectile(const Tuple& p, const Tuple& v) : position(p), velocity(v)
{
    this->position.toPoint();
    this->velocity.toVector();
}

Projectile::Projectile(const Projectile& that)
{
    this->position = that.position;
    this->velocity = that.velocity;
}

// copy assignment 
Projectile& Projectile::operator=(const Projectile& that)
{
    if(this != &that)
    {
        //std::swap(this->position, that.position);
        //std::swap(this->velocity, that.velocity);
        this->position = that.position;
        this->velocity = that.velocity;
    }

    return *this;
}

/*
 * ==
 */
bool Projectile::operator==(const Projectile& that) const
{
    if(this->position != that.position)
        return false;
    if(this->velocity != that.velocity)
        return false;

    return true;
}

/*
 * !=
 */
bool Projectile::operator!=(const Projectile& that) const
{
    return !(*this == that);
}

/*
 * toString()
 */
std::string Projectile::toString(void) const
{
    std::ostringstream oss;

    oss << "Projectile( P(" << this->position.x << ", " << this->position.y << ", " << this->position.z << ")";
    oss << " V(" << this->velocity.x << ", " << this->velocity.y << ", " << this->velocity.z << ")";

    return oss.str();
}


/*
 * ================ ENVIRONMENT ================ 
 */
Environment::Environment() : gravity(Tuple()), wind(Tuple())
{
    this->gravity.toVector();
    this->wind.toVector();
}

Environment::Environment(const Tuple& g, const Tuple& w) : gravity(g), wind(w)
{
    this->gravity.toVector();
    this->wind.toVector();
}


/*
 * ==
 */
bool Environment::operator==(const Environment& that) const
{
    if(this->gravity != that.gravity)
        return false;
    if(this->wind != that.wind)
        return false;

    return true;
}

/*
 * !=
 */
bool Environment::operator!=(const Environment& that) const
{
    return !(*this == that);
}

/*
 * toString()
 */
std::string Environment::toString(void) const
{
    std::ostringstream oss;

    oss << "Environment( G(" << this->gravity.x << ", " << this->gravity.y << ", " << this->gravity.z << ")";
    oss << " W(" << this->wind.x << ", " << this->wind.y << ", " << this->wind.z << "))";

    return oss.str();
}



/*
 * Tick function.
 * From book - this may get adapted into something else later
 */
Projectile tick(const Environment& env, const Projectile& p)
{
    Projectile pp;

    pp.position = p.position + p.velocity;
    pp.velocity = p.velocity + env.gravity + env.wind;

    return pp;
}
