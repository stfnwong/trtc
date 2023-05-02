/*
 * Template Matrx 
 * Once this works it might become the standard TMatrix implementation for this project
 */

#ifndef __TMATRIX_HPP
#define __TMATRIX_HPP

#include <array>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include "Common.hpp"
#include "Tuple.hpp"


/*
 * Templated Matrix 
 */
template <int ROWS, int COLS> class TMatrix
{
    public:     // TODO: protected?
        float data[ROWS * COLS];

    private:
        int rc_to_idx(int r, int c) const;

    public:
        // constructors
        //explicit TMatrix(const std::vector<float>& vals);
        TMatrix();
        TMatrix(const std::vector<float>& vals);
        TMatrix(std::initializer_list<float> vals);
        TMatrix(std::initializer_list<std::initializer_list<float>> vals);

        // operators
        float operator()(int r, int c) const;
        float& operator()(int r, int c);

        bool operator==(const TMatrix& that) const;
        bool operator!=(const TMatrix& that) const;

        // Mathematical operators
        TMatrix operator*(const TMatrix& that) const;     
        Tuple operator*(const Tuple& that) const;     
        // TODO: multiply with Tuple

        // utils 
        //
        std::array<int, 2>      shape(void) const;
        TMatrix<ROWS-1, COLS-1> submatrix(int r, int c) const;
        void                    transpose(void);
        TMatrix<ROWS, COLS>     transposed(void) const;

        //float det(void) const;
        //float minor(int r, int int c) const;
        //float cofactor(int r, int int c) const;

        std::string toString(void) const;
};


// Index conversion
template <int ROWS, int COLS> int TMatrix<ROWS, COLS>::rc_to_idx(int r, int c) const
{
    return (r * COLS) + c;
}

// ================ CONSTRUCTORS ================ //

// Ctor from flat array
template <int ROWS, int COLS> TMatrix<ROWS, COLS>::TMatrix()
{
    if(ROWS == 0 || COLS == 0)
        throw std::range_error("TMatrix: 0-size dimension is undefined");

    // zero out memory 
    for(int rr = 0; rr < ROWS; ++rr)
    {
        for(int cc = 0; cc < COLS; ++cc)
            this->data[this->rc_to_idx(rr, cc)] = 0.0f;
    }
}


// Ctor from flat array
template <int ROWS, int COLS> TMatrix<ROWS, COLS>::TMatrix(const std::vector<float>& vals)
{
    if(vals.size() != ROWS * COLS)
        throw std::range_error("TMatrix(vector<float> vals)");

    auto it = vals.begin();
    for(int r = 0; r < ROWS; ++r)
    {
        for(int c = 0; c < COLS; ++c)
        {
            this->data[this->rc_to_idx(r, c)] = *it;
            it++;
        }
    }
}


// Ctor from flat initializer_list
template <int ROWS, int COLS> TMatrix<ROWS, COLS>::TMatrix(std::initializer_list<float> vals)
{
    if(vals.size() != ROWS * COLS)
        throw std::range_error("TMatrix(vector<float> vals)");

    auto it = vals.begin();
    for(int r = 0; r < ROWS; ++r)
    {
        for(int c = 0; c < COLS; ++c)
        {
            this->data[this->rc_to_idx(r, c)] = *it;
            it++;
        }
    }
}

// Ctor from initializer_list of  initializer_list s
template <int ROWS, int COLS> TMatrix<ROWS, COLS>::TMatrix(std::initializer_list<std::initializer_list<float>> vals)
{
    int rr = 0;
    for(auto row :vals)
    {
        if(rr >= ROWS)
            break;

        int cc = 0;
        for(auto val : row)
        {
            if(cc >= COLS)
                break;

            this->data[this->rc_to_idx(rr, cc)] = val;
            cc++;
        }
        rr++;
    }
}



// ================ OPERATORS ================ //
template <int ROWS, int COLS> float TMatrix<ROWS, COLS>::operator()(int r, int c) const
{
    if(r >= ROWS || c >= COLS)
        throw std::out_of_range("Subscript out of bounds");
    return this->data[rc_to_idx(r, c)];
}

template <int ROWS, int COLS> float& TMatrix<ROWS, COLS>::operator()(int r, int c)
{
    if(r >= ROWS || c >= COLS)
        throw std::out_of_range("Subscript out of bounds");
    return this->data[rc_to_idx(r, c)];
}

template<int ROWS, int COLS> bool TMatrix<ROWS, COLS>::operator==(const TMatrix& that) const
{
    for(int rr = 0; rr < ROWS; ++rr)
    {
        for(int cc = 0; cc < COLS; ++cc)
        {
            if(!equal_eps(this->data[rc_to_idx(rr, cc)], that.data[this->rc_to_idx(rr, cc)], 1e-6))
                return false;
        }
    }

    return true;
}

template<int ROWS, int COLS> bool TMatrix<ROWS, COLS>::operator!=(const TMatrix& that) const
{
    return !(*this == that);
}

// ================ MATHEMATICAL OPERATORS ================ //
/*
 * Mutiply with TMatrix
 */
template <int ROWS, int COLS> TMatrix<ROWS, COLS> TMatrix<ROWS, COLS>::operator*(const TMatrix& that) const
{
    TMatrix<ROWS, COLS> out_mat;

    // TODO : add exception here

    int rr, cc, kk;
    float elem;

    for(rr = 0; rr < ROWS; ++rr)
    {
        for(cc = 0; cc < COLS; ++cc)
        {
            elem = 0.0;
            for(kk = 0; kk < COLS; ++kk)
                elem += this->data[this->rc_to_idx(rr, kk)] * that(kk, cc);
            out_mat(rr, cc) = elem;
        }
    }

    return out_mat;
}

/*
 * Mutiply with Tuple
 */
template <int ROWS, int COLS> Tuple TMatrix<ROWS, COLS>::operator*(const Tuple& that) const
{
    Tuple out_tuple;

    int rr, kk;
    float elem;

    for(rr = 0; rr < ROWS; ++rr)
    {
        elem = 0.0;
        for(kk = 0; kk < COLS; ++kk)
        {
            elem += this->data[this->rc_to_idx(rr, kk)] * that[kk];
        }
        out_tuple[rr] = elem;
    }

    return out_tuple;
}


// ================ MATHEMATICAL OPERATORS ================ //
template <int ROWS, int COLS> std::array<int, 2> TMatrix<ROWS, COLS>::shape(void) const
{
    return std::array<int, 2>{ROWS, COLS};
}

template <int ROWS, int COLS> TMatrix<ROWS-1, COLS-1> TMatrix<ROWS, COLS>::submatrix(int r, int c) const
{
    TMatrix<ROWS-1, COLS-1> submat;

    int co = 0;
    int ro = 0;

    for(int rr = 0; rr < ROWS; ++rr)
    {
        if(rr == r)
            continue;
        for(int cc = 0; cc < COLS; ++cc)
        {
            if(cc == c)
                continue;
            submat(ro, co) = this->data[this->rc_to_idx(rr, cc)];
            co++;
        }
        co = 0;
        ro++;
    }

    return submat;
}

/*
 * transpose()
 */
template <int ROWS, int COLS> void TMatrix<ROWS, COLS>::transpose(void) 
{
    for(int rr = 0; rr < (ROWS-1); ++rr)
    {
        for(int cc = (rr+1); cc < COLS; ++cc)
        {
            std::swap(
                    this->data[this->rc_to_idx(rr, cc)],
                    this->data[this->rc_to_idx(cc, rr)]
            );
        }
    }
}

/*
 * transposed()
 */
template <int ROWS, int COLS> TMatrix<ROWS, COLS> TMatrix<ROWS, COLS>::transposed(void) const
{
    TMatrix<ROWS, COLS> out_mat;

    for(int rr = 0; rr < COLS; ++rr)
    {
        for(int cc = 0; cc < COLS; ++cc)
            out_mat(rr, cc) = this->data[this->rc_to_idx(cc, rr)];
    }

    return out_mat;
}



/*
 * toString()
 * Note that this will tend to be quite slow
 */
template <int ROWS, int COLS> std::string TMatrix<ROWS, COLS>::toString(void) const
{
    std::ostringstream oss;

    oss << "Matrix(" << std::dec << ROWS << "," << COLS << ")" << std::endl;
    for(int r = 0; r < ROWS; ++r)
    {
        for(int c = 0; c < COLS; ++c)
        {
            oss << std::setw(4) << std::left << this->data[this->rc_to_idx(r, c)] << " ";
        }
        oss << std::endl;

    }

    return oss.str();
}



// ================ IDENTITY ================ //
//template <int ROWS, int COLS> TMatrix<ROWS, COLS> TMatrix<ROWS, COLS>::


using Mat2 = TMatrix<2, 2>;
using Mat3 = TMatrix<3, 3>;
using Mat4 = TMatrix<4, 4>;


// TODO: Try to inherit instead, since we can overload specialities like mutiply or identity



#endif /*__TMATRIX_HPP*/
