#ifndef _MY_VECTOR_H_INCLUDED
#define _MY_VECTOR_H_INCLUDED

#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <algorithm>

const int defolt_cp = 2;
class MyVector
{
public:
    MyVector() : MyVector(defolt_cp) {};
    MyVector(std::size_t init_capacity);
    ~MyVector();
    MyVector(const MyVector &v);

    MyVector &operator=(const MyVector &v);
    void set(std::size_t index, int value);
    int get(std::size_t index);

    std::size_t size();
    std::size_t capacity();

    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size);

    void push_back(int value);
    void insert(std::size_t index, int value);
    void erase(std::size_t index);

private: 
    void assign(const MyVector &v);
    std::size_t _sz, _cp;
    int *_data;
};

#endif