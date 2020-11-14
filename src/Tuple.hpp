/*
 * TUPLE
 * A ordered set of numbers 
 */

#ifndef __TUPLE_HPP
#define __TUPLE_HPP

#include <string>

/*
 * Tuple
 * Ordered set of numbers 
 */
// TODO: if it makes sense later this could be templated (to switch from float
// to double, for instance)
struct Tuple
{
    float x;
    float y;
    float z;
    float w;

    public:
        Tuple();
        Tuple(float x_new, float y_new, float z_new);
        Tuple(float x_new, float y_new, float z_new, float w_new);
        Tuple(const Tuple& that) = default;
        Tuple(Tuple&& that) = default;

        // operators 
        bool operator==(const Tuple& that) const;
        bool operator!=(const Tuple& that) const;
        // arithmetic + assignment 
        Tuple& operator+=(const Tuple& that);
        Tuple& operator-=(const Tuple& that);

        Tuple operator+(const Tuple& that) const;
        Tuple operator-(const Tuple& that) const;

        // helpers 
        bool point(void) const;
        bool vector(void) const;
        // string 
        std::string toString(void) const;
        // TODO: serialize?
};


/*
 * Point and Vector factories
 */
Tuple create_vector(float x, float y, float z);
Tuple create_point(float x, float y, float z);


#endif /*__TUPLE_HPP*/
