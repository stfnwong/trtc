/*
 * TRANSFORM
 * Matrix tranforms 
 *
 */

#ifndef __TRANSFORM_HPP
#define __TRANSFORM_HPP


#include "Matrix.hpp"

/*
 * translate()
 */
Matrix translate(float x, float y, float z);
/*
 * scale()
 */
Matrix scale(float x, float y, float z);
/*
 * reflect()
 */
Matrix reflect(float x, float y, float z);

// Rotations 
/*
 * rotate_x()
 */
Matrix rotate_x(float angle);
/*
 * rotate_y()
 */
Matrix rotate_y(float angle);

/*
 * rotate_z()
 */
Matrix rotate_z(float angle);



#endif /*__TRANSFORM_HPP*/
