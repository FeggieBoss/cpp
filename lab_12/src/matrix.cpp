#include "matrix.h"
using namespace matrix;

void Matrix::init(std::size_t r, std::size_t c)
{
    _rows = r;
    _cols = c;
    _data = new int *[r];
    _data[0] = new int[r * c]();
    for (std::size_t i = 1; i < r; ++i)
        _data[i] = (int *)(_data[0] + i * c);
}

Matrix::Matrix() : _rows(init_proportions), _cols(init_proportions)
{
    _data = nullptr;
}

Matrix::Matrix(std::size_t r, std::size_t c)
{
    init(r, c);
}

void Matrix::clear()
{
    if (_rows)
        delete[] _data[0];

    delete[] _data;
    _rows = _cols = 0;
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
    if (i >= _rows || j >= _cols || i < 0 || j < 0)
        throw MatrixException("ACCESS: bad index.");
    return _data[i][j];
}

void Matrix::print() const
{
    for (std::size_t i = 0; i < _rows; ++i)
    {
        for (std::size_t j = 0; j < _cols; ++j)
        {
            if (j != _cols - 1)
                std::cout << _data[i][j] << " ";
            else
                std::cout << _data[i][j] << std::endl;
        }
    }
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
    Matrix dop = *this + m;

    *this = dop;
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &m)
{
    Matrix dop = *this * m;

    *this = dop;
    return *this;
}

Matrix Matrix::operator+(const Matrix &m) const
{
    if (m.get_rows() != _rows || m.get_cols() != _cols)
        throw MatrixException("ADD: dimensions do not match.");
    Matrix sum = Matrix(m);
    for (std::size_t i = 0; i < _rows; ++i)
        for (std::size_t j = 0; j < _cols; ++j)
            sum._data[i][j] = _data[i][j] + m._data[i][j];
    return sum;
}

Matrix Matrix::operator*(const Matrix &m) const
{
    if (m.get_rows() != _cols)
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    Matrix mul = Matrix(_rows, m.get_cols());
    for (std::size_t i = 0; i < _rows; ++i)
        for (std::size_t j = 0; j < m.get_cols(); ++j)
            for (std::size_t k = 0; k < _cols; ++k)
                mul._data[i][j] += _data[i][k] * m._data[k][j];
    return mul;
}
