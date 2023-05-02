/*
 * MATRIX
 * Objects that implement matricies
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Common.hpp"
#include "Matrix.hpp"



/*
 * ================ MATRIX ================
 */
Matrix::Matrix(unsigned int r, unsigned int c) : rows(r), cols(c) 
{
    if(this->rows == 0 || this->cols == 0)
        throw std::out_of_range("0-size given in Matrix constructor");
    this->data.reserve(this->rows * this->cols);
    this->clear();
}

Matrix::Matrix(unsigned int r, unsigned int c, const std::vector<float>& vals) : rows(r), cols(c)
{
    if(this->rows == 0 || this->cols == 0)
        throw std::out_of_range("0-size given in Matrix constructor");
    if(this->size() > vals.size())
        throw std::out_of_range("Not enough values provided. Need at least " + std::to_string(this->size()) 
                + ", got " + std::to_string(vals.size()));
    this->data = vals;
}

// copy constructor
Matrix::Matrix(const Matrix& that)
{
    //this->data = that.data;
    for(unsigned int i = 0; i < that.size(); ++i)
        this->data[i] =  that.data[i];
    this->rows = that.rows;
    this->cols = that.cols;
}

// copy assignment
Matrix& Matrix::operator=(const Matrix& that)
{
    if(this != &that)
    {
        if(this->size() < that.size())
            this->data.reserve(that.size());

        for(unsigned int i = 0; i < that.size(); ++i)
            this->data[i] = that.data[i];       // TODO: std::copy?

        this->rows = that.rows;
        this->cols = that.cols;
    }
    return *this;
}


unsigned Matrix::rc_to_pos(unsigned int r, unsigned int c) const
{
    return (r * this->cols) + c;
}

/*
 * Comparison 
 */
bool Matrix::operator==(const Matrix& that) const
{
    if(this->rows != that.rows)
        return false;
    if(this->cols != that.cols)
        return false;
    for(unsigned int i = 0; i < this->size(); ++i)
    {
        if(!equal(this->data[i], that.data[i]))
            return false;
    }

    return true;
}

bool Matrix::operator!=(const Matrix& that) const
{
    return !(*this == that);
}

/*
 * Arithmetic
 */
// NOTE: This is a very basic implementation
/*
 * * (Matrix-Matrix)
 */
Matrix Matrix::operator*(const Matrix& that) const
{
    Matrix out_mat(this->rows, that.ncols());

    if(this->cols == that.nrows())
    {
        unsigned int rr, cc, kk;
        float elem;
        for(rr = 0; rr < this->rows; ++rr)
        {
            for(cc = 0; cc < that.ncols(); ++cc)
            {
                elem = 0.0;
                for(kk = 0; kk < this->cols; ++kk)
                    elem += this->data[this->rc_to_pos(rr, kk)] * that(kk, cc);
                out_mat(rr, cc) = elem;
            }
        }
    }
    else        // TODO: out_of_range might not be the right exception to throw...
    {
        throw std::out_of_range("Cannot multiply matrix of size (" + std::to_string(this->rows) 
                + "," + std::to_string(this->cols) + " with matrix of size (" + std::to_string(that.nrows())
                + "," + std::to_string(that.ncols()) + ")");
    }

    return out_mat;
}

/*
 * Matrix-Tuple
 */
Tuple Matrix::operator*(const Tuple& that) const
{
    Tuple out_tuple;

    unsigned int rr, kk;
    float elem;

    for(rr = 0; rr < this->rows; ++rr)
    {
        elem = 0.0;
        for(kk = 0; kk < this->cols; ++kk)
        {
            elem += this->data[this->rc_to_pos(rr, kk)] * that[kk];
        }
        out_tuple[rr] = elem;
    }

    return out_tuple;
}

/*
 * Access operator 
 */
float Matrix::operator()(unsigned r, unsigned c) const
{
    if(r >= this->rows || c >= this->cols)
        throw std::out_of_range("Subscript out of bounds");
    return this->data[this->rc_to_pos(r, c)];
}

float& Matrix::operator()(unsigned r, unsigned c)
{
    if(r >= this->rows || c >= this->cols)
        throw std::out_of_range("Subscript out of bounds");
    return this->data[this->rc_to_pos(r, c)];
}

/*
 * submatrix()
 */
Matrix Matrix::submatrix(unsigned int r, unsigned int c) const
{
    Matrix out_mat(this->rows-1, this->cols-1);

    unsigned int c_out = 0;
    unsigned int r_out = 0;

    for(unsigned int rr = 0; rr < this->rows; ++rr)
    {
        if(rr == r)
            continue;
        for(unsigned cc = 0; cc < this->cols; ++cc)
        {
            if(cc == c)
                continue;
            out_mat(r_out, c_out) = this->data[this->rc_to_pos(rr, cc)];
            c_out++;
        }
        r_out++;
        c_out = 0;
    }

    return out_mat;
}

/*
 * transpose()
 */
Matrix Matrix::transpose(void) const
{
    Matrix out_mat(this->cols, this->rows);

    for(unsigned int rr = 0; rr < this->rows; ++rr)
    {
        for(unsigned int cc = 0; cc < this->cols; ++cc)
            out_mat(cc, rr) = this->data[this->rc_to_pos(rr, cc)];
    }

    return out_mat;
}

/*
 * inverse()
 */
Matrix Matrix::inverse(void) const
{
    Matrix out_mat(this->rows, this->cols);

    if(this->det() == 0.0)
        return out_mat;

    float cf = 0.0;
    for(unsigned int rr = 0; rr < this->rows; ++rr)
    {
        for(unsigned int cc = 0; cc < this->cols; ++cc)
        {
            cf = this->cofactor(rr, cc);
            out_mat(cc, rr) = cf / this->det();
        }
    }

    return out_mat;
}

/*
 * det()
 * TODO : this is only implemented for 2x2 matricies for now 
 */
float Matrix::det(void) const
{
    float det = 0.0;

    if(this->rows == 2 && this->cols == 2)
        det = (this->data[0] * this->data[3]) - (this->data[1] * this->data[2]);
    else
    {
        for(unsigned int cc = 0; cc < this->cols; ++cc)
            det = det + this->data[this->rc_to_pos(0, cc)] * this->cofactor(0, cc);
    }

    return det;
}

/*
 * minor()
 */
float Matrix::minor(unsigned int r, unsigned c) const
{
    Matrix submat = this->submatrix(r, c);
    return submat.det();
}

/*
 * cofactor()
 */
float Matrix::cofactor(unsigned int r, unsigned int c) const
{
    return ((r + c) % 2 == 0) ? this->minor(r, c) : -this->minor(r, c);
}

/*
 * shape()
 */
std::vector<unsigned int> Matrix::shape(void) const
{
    return std::vector<unsigned int>(this->rows, this->cols);
}

/*
 * size()
 */
unsigned Matrix::size(void) const
{
    return this->rows * this->cols;
}

/*
 * nrows()
 */
unsigned int Matrix::nrows(void) const
{
    return this->rows;
}

/*
 * ncols()
 */
unsigned int Matrix::ncols(void) const
{
    return this->cols;
}

/*
 * fill()
 */
void Matrix::fill(float f)
{
    for(unsigned int i = 0; i < this->size(); ++i)
        this->data[i] = f;
}

/*
 * clear()
 */
void Matrix::clear(void)
{
    for(unsigned int i = 0; i < this->size(); ++i)
        this->data[i] = 0.0;
}    

/*
 * toString()
 */
std::string Matrix::toString(void) const
{
    std::ostringstream oss;

    oss << "Matrix(" << std::dec << this->rows << "," << this->cols << ")" << std::endl;
    for(unsigned int r = 0; r < this->rows; ++r)
    {
        for(unsigned int c = 0; c < this->cols; ++c)
        {
            oss << std::setw(4) << std::left << this->data[this->rc_to_pos(r, c)] << " ";
        }
        oss << std::endl;
    }

    return oss.str();
}




/*
 * eye()
 */
Matrix eye(unsigned int size)
{
    Matrix e(size, size);

    for(unsigned int i = 0; i < size; ++i)
        e(i, i) = 1.0;

    return e;
}

/*
 * ones()
 */
Matrix ones(unsigned int r, unsigned int c)
{
    Matrix o(r, c);

    for(unsigned int rr = 0; rr < o.nrows(); ++rr)
    {
        for(unsigned int cc = 0; cc < o.ncols(); ++cc)
        {
            o(rr, cc) = 1.0;
        }
    }

    return o;
}
