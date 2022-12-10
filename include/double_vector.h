#ifndef __DOUBLE_VECTOR_H__
#define __DOUBLE_VECTOR_H__

#include <vector>

namespace LibOptions {

template<typename T>
class DoubleVector {
    std::vector<T> d_data;
    size_t d_index;

    size_t d_numRows;
    size_t d_numCols;
public:
    DoubleVector(int r, int c);

    void set(int i, int j, const T& val);
    const T& get(int i, int j) const;
    T& get(int i, int j);
};

template<typename T>
DoubleVector<T>::DoubleVector(int r, int c)
    : d_data(r * c, T()), d_index(0), d_numRows(r), d_numCols(c)
{}

template<typename T>
void DoubleVector<T>::set(int i, int j, const T& val)
{
    int index = i * d_numCols + j;
    d_data[index] = val;
}

template<typename T>
const T& DoubleVector<T>::get(int i, int j) const
{
    int index = i * d_numCols + j;
    return d_data[index];
}

template<typename T>
T& DoubleVector<T>::get(int i, int j)
{
    int index = i * d_numCols + j;
    return d_data[index];
}

} // namespace LibOptions

#endif