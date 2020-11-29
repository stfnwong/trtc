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
 * Generate a rotation matrix that rotates a point about 
 * the x-axis by a given angle.
 */
Matrix rotate_x(float angle);
/*
 * rotate_y()
 * Generate a rotation matrix that rotates a point about 
 * the y-axis by a given angle.
 */
Matrix rotate_y(float angle);

/*
 * rotate_z()
 * Generate a rotation matrix that rotates a point about 
 * the z-axis by a given angle.
 */
Matrix rotate_z(float angle);



/*
 * shear()
 */
Matrix shear(float xy, float xz, float yx, float yz, float zx, float zy);

#endif /*__TRANSFORM_HPP*/
