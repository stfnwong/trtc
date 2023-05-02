/*
 * MATRIX
 * Objects that implement matricies
 */

#ifndef __MATRIX_HPP
#define __MATRIX_HPP

#include <string>
#include <vector>

#include "Tuple.hpp"

// TODO: do a template version as well...

/*
 * A Matrix. Because this is a raytracer we only need to implement 2d
 * matricies 
 */
class Matrix
{
    private:
        unsigned int rows;
        unsigned int cols;
        std::vector<float> data;

    private:
        // NOTE: generic enough that it could just be a function in this scope?
        unsigned rc_to_pos(unsigned int r, unsigned int c) const;

    public:
        Matrix(unsigned int r, unsigned int c);
        Matrix(unsigned int r, unsigned int c, const std::vector<float>& vals);
        Matrix(const Matrix& that);

        // def need copy assignment 
        Matrix& operator=(const Matrix& that);
        // TODO: also need move assignment?

        // comparison
        bool operator==(const Matrix& that) const;
        bool operator!=(const Matrix& that) const;

        // Arithmetic 
        Matrix operator*(const Matrix& that) const;
        Tuple  operator*(const Tuple& that) const;

        // access 
        float  operator()(unsigned r, unsigned c) const;
        float& operator()(unsigned r, unsigned c);

        /*
         * submatrix()
         *
         * Return a matrix with the row r and column c removed. The contents
         * of this matrix object are not modified.
         */
        Matrix submatrix(unsigned int r, unsigned int c) const;
        /*
         * transpose()
         *
         * Return the transpose of the matrix. The contents of this matrix 
         * object are not modified
         */
        Matrix transpose(void) const;
        /*
         * inverse()
         *
         * Return the inverse of the matrix. The contents of this matrix 
         * object are not modified
         */
        Matrix inverse(void) const;
        //Matrix tr(void);      // TODO: in-place transpose
        float det(void) const;
        float minor(unsigned int r, unsigned int c) const;
        float cofactor(unsigned int r, unsigned int c) const;

        std::vector<unsigned int> shape(void) const;
        unsigned int size(void) const;
        unsigned int nrows(void) const;
        unsigned int ncols(void) const;
        void fill(float f);
        void clear(void);

        /*
         * chain()
         * Chain a sequence of matrix multiplications together 
         */
        // TODO: this should go into Transform.hpp instead
        //template <typename... Mats> chain(Mats... mats)         // TODO: could be const?
        //{
        //}

        /*
         * toString()
         * Return string representation
         */
        std::string toString(void) const;
};


/*
 * Get an Identity Matrix
 */
Matrix eye(unsigned int size);
/*
 * Get a Matrix of ones
 */
Matrix ones(unsigned int r, unsigned int c);


#endif /*__MATRIX_HPP*/
