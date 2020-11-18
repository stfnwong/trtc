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
        throw std::out_of_range("Not enough value provided. Need at least " + std::to_string(this->size()) 
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


unsigned Matrix::xy_to_pos(unsigned int r, unsigned int c) const
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
 * Access operator 
 */
float Matrix::operator()(unsigned r, unsigned c) const
{
    if(r >= this->rows || c >= this->cols)
        throw std::out_of_range("Subscript out of bounds");
    return this->data[this->xy_to_pos(r, c)];
}

float& Matrix::operator()(unsigned r, unsigned c)
{
    if(r >= this->rows || c >= this->cols)
        throw std::out_of_range("Subscript out of bounds");
    return this->data[this->xy_to_pos(r, c)];
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
            oss << std::setw(4) << std::left << this->data[this->xy_to_pos(r, c)] << " ";
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
