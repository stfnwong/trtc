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
        TMatrix();
        TMatrix(float v);           // ctor to fill with value
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
        std::array<int, 2>      shape(void) const;
        int                     rows(void) const;
        int                     cols(void) const;

        // Matrix ops 
        TMatrix<ROWS-1, COLS-1> submatrix(int r, int c) const;
        float                   minor(int r, int c) const;
        float                   cofactor(int r, int c) const;
        float                   det(void) const;

        void                    transpose(void);
        void                    inverse(void);
        TMatrix<ROWS, COLS>     transposed(void) const;
        TMatrix<ROWS, COLS>     inversed(void) const;

        std::string toString(void) const;

        template <int R = ROWS, int C = COLS> typename std::enable_if<(R > 2) && (C > 2), float>::type
        minor(int r, int c) const;
        //{
        //    return this->submatrix(r, c).det();

        //    //TMatrix<ROWS-1, COLS-1> submat = this->submatrix(r, c);
        //    //return submat.det();
        //}

        //template <int R = ROWS, int C = COLS> typename std::enable_if<(R == 2) && (C == 2), float>::type
        //det(void) const
        //{
        //    return (this->data[0] * this->data[3]) - (this->data[1] * this->data[2]);
        //}

};


// Index conversion
template <int ROWS, int COLS> int TMatrix<ROWS, COLS>::rc_to_idx(int r, int c) const
{
    return (r * COLS) + c;
}

// ================ CONSTRUCTORS ================ //
template <int ROWS, int COLS> TMatrix<ROWS, COLS>::TMatrix(float v)
{
    if(ROWS == 0 || COLS == 0)
        throw std::range_error("TMatrix: 0-size dimension is undefined");

    for(int rr = 0; rr < ROWS; ++rr)
    {
        for(int cc = 0; cc < COLS; ++cc)
            this->data[this->rc_to_idx(rr, cc)] = v;
    }
}

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


// ================ UTILS ================ //
template <int ROWS, int COLS> std::array<int, 2> TMatrix<ROWS, COLS>::shape(void) const
{
    return std::array<int, 2>{ROWS, COLS};
}

template <int ROWS, int COLS> int TMatrix<ROWS, COLS>::rows(void) const
{
    return ROWS;
}

template <int ROWS, int COLS> int TMatrix<ROWS, COLS>::cols(void) const
{
    return COLS;
}



// ================ MATRIX OPERATORS ================ //


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
 * minor()
 */
//template <int ROWS, int COLS> float TMatrix<ROWS, COLS>::minor(int r, int c) const 
//template <int R = ROWS, int C = COLS> typename std::enable_if<(R > 2) && (C > 2), float>::type
//TMatrix<ROWS, COLS>::minor(int r, int c) const
//{
//    return this->submatrix(r, c).det();
//
//    //TMatrix<ROWS-1, COLS-1> submat = this->submatrix(r, c);
//    //return submat.det();
//}
//

/*
 * cofactor()
 */
template <int ROWS, int COLS> float TMatrix<ROWS, COLS>::cofactor(int r, int c) const 
{
    return this->minor(r, c) * (((r+c) % 2 == 0) ? 1 : -1);
    //return ((ROWS + COLS) % 2 == 0) ? this->minor(r, c) : -this->minor(r, c);
}

/*
 * det()
 * Compute determinant of this matrix
 */
//template <int R = ROWS, int C = COLS> typename std::enable_if<(R == 2) && (C == 2), float>::type
//TMatrix<ROWS, COLS>::det(void) const
//{
//    return (this->data[0] * this->data[3]) - (this->data[1] * this->data[2]);
//}

template <int ROWS, int COLS> float TMatrix<ROWS, COLS>::det(void) const
{
    float det = 0.0;

    for(int cc = 0; cc < COLS; ++cc)
        det = det + this->data[this->rc_to_idx(0, cc)] * this->cofactor(0, cc);

    return det;
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
 * Return a copy of the transpose of this matrix
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
 * inversed()
 * Return a copy of the inverse of this matrix 
 */
template <int ROWS, int COLS> TMatrix<ROWS, COLS> TMatrix<ROWS, COLS>::inversed(void) const
{
    TMatrix<ROWS, COLS> out_mat;

    if(this->det() == 0.0)
        return out_mat;

    float cf = 0.0;
    float inv_det = 1.0f / this->det();

    for(int rr = 0; rr < ROWS; ++rr)
    {
        for(int cc = 0; cc < COLS; ++cc)
        {
            cf = this->cofactor(rr, cc);
            out_mat(cc, rr) = cf * inv_det;
        }
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

// Generate identity matrix
template <typename T> T eye(void)
{
    //TMatrix<SIZE, SIZE> eye_mat;
    T eye_mat;
    if(eye_mat.shape()[0] != eye_mat.shape()[1])
        throw std::range_error("eye matrix only defined when ROWS == COLS");

    for(int ii = 0; ii < eye_mat.shape()[0]; ++ii)
        eye_mat(ii, ii) = 1.0f;

    return eye_mat;
}

// Generate ones matrix 
template <typename T> T ones(void)
{
    return T(1.0);
}


using Mat2 = TMatrix<2, 2>;
using Mat3 = TMatrix<3, 3>;
using Mat4 = TMatrix<4, 4>;





#endif /*__TMATRIX_HPP*/
