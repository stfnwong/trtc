/*
 * MATRIX
 * Objects that implement matricies
 */

#ifndef __MATRIX_HPP
#define __MATRIX_HPP

#include <string>
#include <vector>

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
        unsigned xy_to_pos(unsigned int r, unsigned int c) const;

    public:
        Matrix(unsigned int r, unsigned int c);
        Matrix(unsigned int r, unsigned int c, const std::vector<float>& vals);
        Matrix(const Matrix& that);

        // def need copy assignment 
        Matrix& operator=(const Matrix& that);
        // TODO: also need move assignment

        // comparison
        bool operator==(const Matrix& that) const;
        bool operator!=(const Matrix& that) const;

        // Arithmetic 

        // access 
        float  operator()(unsigned r, unsigned c) const;
        float& operator()(unsigned r, unsigned c);

        std::vector<unsigned int> shape(void) const;
        unsigned int size(void) const;
        unsigned int nrows(void) const;
        unsigned int ncols(void) const;
        void clear(void);

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
