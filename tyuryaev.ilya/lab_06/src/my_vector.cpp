#include "my_vector.h"

MyVector::MyVector(std::size_t init_capacity)
{
    _sz = 0;
    _cp = init_capacity;
    _data = (int *)malloc(_cp * sizeof(int));
}
MyVector::~MyVector()
{
    _sz = _cp = 0;
    free(_data);
    _data = nullptr;
}
void MyVector::assign(const MyVector &v)
{
    _sz = v._sz;
    _cp = v._cp;
    _data = (int *)malloc(_cp * sizeof(int));
    memcpy(_data, v._data, _sz * sizeof(int));
}
MyVector::MyVector(const MyVector &v)
{
    assign(v);
}
MyVector &MyVector::operator=(const MyVector &v)
{
    if (&v == this)
        return *this;
    free(_data);

    assign(v);
    return *this;
}

void MyVector::set(std::size_t index, int value)
{
    _data[index] = value;
}
int MyVector::get(std::size_t index)
{
    return _data[index];
}

std::size_t MyVector::size()
{
    return _sz;
}
std::size_t MyVector::capacity()
{
    return _cp;
}

void MyVector::reserve(std::size_t new_capacity)
{
    if (new_capacity <= _cp)
        return;
    _cp = new_capacity;
    _data = (int *)realloc(_data, _cp * sizeof(int));
}
void MyVector::resize(std::size_t new_size)
{
    if (_cp < new_size)
        reserve(std::max(new_size, 2 * _cp));
    if (_sz < new_size)
        memset(_data + _sz, 0, (new_size - _sz) * sizeof(int));
    _sz = new_size;
}

void MyVector::push_back(int value)
{
    if (_sz == _cp)
        reserve(2 * _cp);
    _data[_sz++] = value;
}
void MyVector::insert(std::size_t index, int value)
{
    if (_sz == _cp)
        reserve(2 * _cp);
    memmove(_data + index + 1, _data + index, (_sz - index) * sizeof(int));
    _data[index] = value;
    _sz++;
}
void MyVector::erase(std::size_t index)
{
    assert(index < _sz);
    memmove(_data + index, _data + index + 1, (_sz - index - 1) * sizeof(int));
    _sz--;
}
