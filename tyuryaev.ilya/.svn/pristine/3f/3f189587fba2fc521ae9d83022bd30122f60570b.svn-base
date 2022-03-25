#include "my_vector.h"

template <typename T>
containers::my_vector<T>::my_vector() : capacity_(init_cp), size_(init_sz)
{
    array_ = (T *)new char[capacity_ * sizeof(T)];
}

template <typename T>
containers::my_vector<T>::my_vector(std::size_t n)
{
    capacity_ = init_cp;
    while (capacity_ < n)
        capacity_ *= cp_multiplier;

    size_ = n;
    array_ = (T *)(new char[capacity_ * sizeof(T)]);
    for (std::size_t i = 0; i < size_; ++i)
        new (&array_[i]) T();
}

template <typename T>
const T &containers::my_vector<T>::operator[](std::size_t index) const
{
    return array_[index];
}

template <typename T>
T &containers::my_vector<T>::operator[](std::size_t index)
{
    return array_[index];
}

template <typename T>
void containers::my_vector<T>::move_array(T *to, T *from, std::size_t numb)
{
    for (std::size_t i = 0; i < numb; ++i)
        new (&to[i]) T(from[i]);
}

template <typename T>
void containers::my_vector<T>::assign(const my_vector<T> &other)
{
    capacity_ = other.capacity_;
    size_ = other.size_;
    array_ = (T *)new char[capacity_ * sizeof(T)];
    move_array(array_, other.array_, size_);
}

template <typename T>
void containers::my_vector<T>::free_vec(my_vector<T> &vec, std::size_t from)
{
    for (std::size_t i = from; i < size_; ++i)
        vec[i].~T();
}

template <typename T>
containers::my_vector<T>::my_vector(const my_vector<T> &other)
{
    assign(other);
}

template <typename T>
containers::my_vector<T> &containers::my_vector<T>::operator=(my_vector<T> other)
{
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(array_, other.array_);
    return *this;
}

template <typename T>
containers::my_vector<T>::~my_vector()
{
    free_vec(*this);
    delete[](char *) array_;
    capacity_ = size_ = 0;
    array_ = nullptr;
}

template <typename T>
std::size_t containers::my_vector<T>::size() const
{
    return size_;
}

template <typename T>
std::size_t containers::my_vector<T>::capacity() const
{
    return capacity_;
}

template <typename T>
bool containers::my_vector<T>::empty() const
{
    return (size_ == (std::size_t)0);
}

template <typename T>
void containers::my_vector<T>::reserve(std::size_t n)
{
    if (n <= capacity_)
        return;
    while (capacity_ < n)
        capacity_ *= cp_multiplier;

    T *mem = (T *)new char[capacity_ * sizeof(T)];
    move_array(mem, array_, size_);
    free_vec(*this);
    delete[](char *) array_;
    array_ = mem;
}

template <typename T>
void containers::my_vector<T>::resize(std::size_t n)
{
    reserve(n);
    if (size_ <= n)
    {
        for (std::size_t i = size_; i < n; ++i)
            new (&array_[i]) T();
    }
    else
        free_vec(*this, n);

    size_ = n;
}

template <typename T>
void containers::my_vector<T>::push_back(const T t)
{
    if (size_ == capacity_)
        reserve(cp_multiplier * capacity_);
    new (&array_[size_++]) T(t);
}

template <typename T>
void containers::my_vector<T>::pop_back()
{
    array_[--size_].~T();
}

template <typename T>
void containers::my_vector<T>::clear()
{
    free_vec(*this);
    size_ = 0;
}