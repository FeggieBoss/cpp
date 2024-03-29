#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <cstring>
#include <cassert>
#include <iostream>

namespace containers
{
    const std::size_t cp_multiplier = 2;
    const std::size_t init_cp = 1;
    const std::size_t init_sz = 0;

    template <typename T>
    class my_vector
    {
    public:
        my_vector();
        explicit my_vector(std::size_t n);
        my_vector(const my_vector<T> &other);
        my_vector<T> &operator=(my_vector<T> other);
        ~my_vector();

        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;

        void resize(std::size_t n);
        void reserve(std::size_t n);

        const T &operator[](std::size_t index) const;
        T &operator[](std::size_t index);

        template <typename K>
        friend std::ostream &operator<<(std::ostream &out, const my_vector<K> &my_vec);

        void push_back(const T t);
        void pop_back();
        void clear();

    private:
        void assign(const my_vector<T> &other);
        void free_vec(my_vector<T> &vec, std::size_t from = 0);
        void move_array(T *to, T *from, std::size_t numb);

    private:
        std::size_t capacity_;
        std::size_t size_;
        T *array_;
    };

    template <typename K>
    std::ostream &operator<<(std::ostream &out, const my_vector<K> &my_vec)
    {
        for (std::size_t i = 0; i < my_vec.size_; ++i)
        {
            out << my_vec[i];
            if (i != my_vec.size_ - 1)
                out << " ";
        }
        return out;
    }
} // namespace containers

#include "my_vector_impl.h"

#endif // MY_VECTOR_H_
