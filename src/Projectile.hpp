/*
 * PROJECTILE
 * This is just a little test of the vector and point implementation
 */

#ifndef __PROJECTILE_HPP
#define __PROJECTILE_HPP

#include "Tuple.hpp"


struct Projectile
{
    Tuple position;     // point
    Tuple velocity;     // vector

    public:
        Projectile();
        Projectile(const Tuple& p, const Tuple& v);
        Projectile(const Projectile& that);
        // we need copy assignment 
        Projectile& operator=(const Projectile& that);

        bool operator==(const Projectile& that) const;
        bool operator!=(const Projectile& that) const;


        std::string toString(void) const;
};



struct Environment
{
    Tuple gravity;      // vector
    Tuple wind;         // vector

    public:
        Environment();
        Environment(const Tuple& g, const Tuple& w);
        Environment(const Environment& that) = default;
        Environment(Environment&& that) = default;

        bool operator==(const Environment& that) const;
        bool operator!=(const Environment& that) const;

        std::string toString(void) const;
};



Projectile tick(const Environment& env, const Projectile& p);



#endif /*__PROJECTILE_HPP*/
