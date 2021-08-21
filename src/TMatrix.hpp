/*
 * Template Matrx 
 * Once this works it might become the standard TMatrix implementation for this project
 */

#ifndef __TMATRIX_HPP
#define __TMATRIX_HPP

#include <initializer_list>
#include <stdexcept>
#include <vector>


template <int ROWS, int COLS> class TMatrix
{
    public:     // TODO: protected?
        float data[ROWS * COLS];

    private:
        unsigned rc_to_pos(unsigned int r, unsigned int c) const;

    public:
        // constructors
        //explicit TMatrix(const std::vector<float>& vals);
        TMatrix(const std::vector<float>& vals);
        TMatrix(std::initializer_list<float> vals);
        TMatrix(std::initializer_list<std::initializer_list<float>> vals);

        // operators
        float operator()(unsigned r, unsigned c) const;
        float& operator()(unsigned r, unsigned c);
};


// Index conversion

    return (r * COLS) + c;
}

// ================ CONSTRUCTORS ================ //
// Ctor from flat array
template <int ROWS, int COLS> TMatrix<ROWS, COLS>::TMatrix(const std::vector<float>& vals)
{
    if(vals.size() != ROWS * COLS)
        throw std::range_error("TMatrix(vector<float> vals)");

    auto it = vals.begin();
    for(unsigned r = 0; r < ROWS; ++r)
    {
        for(unsigned c = 0; c < COLS; ++c)
        {
            this->data[this->rc_to_pos(r, c)] = *it;
            it++;
        }
    }
}


// Ctor from flat initializer_list
template <int ROWS, int COLS> TMatrix<ROWS, COLS>::TMatrix(std::initializer_list<float> vals)
{
    auto it = vals.begin();
    for(unsigned r = 0; r < ROWS; ++r)
    {
        for(unsigned c = 0; c < COLS; ++c)
        {
            this->data[this->rc_to_pos(r, c)] = *it;
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

            this->data[this->rc_to_pos(rr, cc)] = val;
            cc++;
        }
        rr++;
    }
}

// ================ OPERATORS ================ //
template <int ROWS, int COLS> float TMatrix<ROWS, COLS>::operator()(unsigned r, unsigned c) const
{
    if(r >= ROWS || c >= COLS)
        throw std::out_of_range("Subscript out of bounds");
    return this->data[rc_to_pos(r, c)];
}

template <int ROWS, int COLS> float& TMatrix<ROWS, COLS>::operator()(unsigned r, unsigned c)
{
    if(r >= ROWS || c >= COLS)
        throw std::out_of_range("Subscript out of bounds");
    return this->data[rc_to_pos(r, c)];
}



#endif /*__TMATRIX_HPP*/
