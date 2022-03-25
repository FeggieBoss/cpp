#include "matrix.h"

void Matrix::init(std::size_t r, std::size_t c)
{
    _rows = r;
    _cols = c;
    _data = new int *[r];
    _data[0] = new int[r * c]();
    for (std::size_t i = 1; i < r; ++i)
        _data[i] = (int *)(_data[0] + i * c);
}
Matrix::Matrix(std::size_t r, std::size_t c)
{
    init(r, c);
}

void Matrix::clear()
{
    _rows = _cols = 0;
    delete[] _data[0];
    delete[] _data;
    _data = nullptr;
}
Matrix::~Matrix()
{
    clear();
}

void Matrix::copy(const Matrix &m)
{
    for (std::size_t i = 0; i < _rows; ++i)
        for (std::size_t j = 0; j < _cols; ++j)
            _data[i][j] = m._data[i][j];
}
Matrix::Matrix(const Matrix &m) : Matrix(m._rows, m._cols)
{
    copy(m);
}

std::size_t Matrix::get_rows() const
{
    return _rows;
}
std::size_t Matrix::get_cols() const
{
    return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val)
{
    _data[i][j] = val;
}
int Matrix::get(std::size_t i, std::size_t j) const
{
    return _data[i][j];
}

void Matrix::print(FILE *f) const
{
    for (std::size_t i = 0; i < _rows; ++i)
    {
        for (std::size_t j = 0; j < _cols; ++j)
        {
            if (j != _cols - 1)
                fprintf(f, "%d ", _data[i][j]);
            else
                fprintf(f, "%d\n", _data[i][j]);
        }
    }
}

bool Matrix::operator==(const Matrix &m) const
{
    bool flag = true;
    for (std::size_t i = 0; i < _rows; ++i)
        for (std::size_t j = 0; j < _cols; ++j)
            if (_data[i][j] != m._data[i][j])
                flag = false;
    return flag;
}

bool Matrix::operator!=(const Matrix &m) const
{
    return !(*this == m);
}

Matrix &Matrix::operator=(const Matrix &m)
{
    if (&m == this)
        return *this;
    clear();
    init(m._rows, m._cols);
    copy(m);
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &m)
{
    *this = *this + m;
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &m)
{
    *this = *this - m;
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &m)
{
    *this = *this * m;
    return *this;
}

Matrix Matrix::operator+(const Matrix &m) const
{
    Matrix sum = Matrix(m);
    for (std::size_t i = 0; i < _rows; ++i)
        for (std::size_t j = 0; j < _cols; ++j)
            sum._data[i][j] = _data[i][j] + m._data[i][j];
    return sum;
}

Matrix Matrix::operator-(const Matrix &m) const
{
    Matrix sub = Matrix(m);
    for (std::size_t i = 0; i < _rows; ++i)
        for (std::size_t j = 0; j < _cols; ++j)
            sub._data[i][j] = _data[i][j] - m._data[i][j];
    return sub;
}

Matrix Matrix::operator*(const Matrix &m) const
{
    Matrix mul = Matrix(_rows, m._cols);
    for (std::size_t i = 0; i < _rows; ++i)
        for (std::size_t j = 0; j < m._cols; ++j)
            for (std::size_t k = 0; k < _cols; ++k)
                mul._data[i][j] += _data[i][k] * m._data[k][j];
    return mul;
}
