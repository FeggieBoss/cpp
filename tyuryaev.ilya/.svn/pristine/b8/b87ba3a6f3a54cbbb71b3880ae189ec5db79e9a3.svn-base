#include <iostream>

#include "my_vector.h"
#include <chrono>
#include <random>

namespace product
{

    class Product
    {
    public:
        Product(const char *name, int quantity, double price) : quantity_(quantity), price_(price)
        {
            copy_name(name);
        }
        ~Product()
        {
            delete[] name_;
        }
        Product(const Product &prod)
        {
            copy_name(prod.name_);
            quantity_ = prod.quantity_;
            price_ = prod.price_;
        }
        friend std::ostream &operator<<(std::ostream &out, const Product &prod);

    private:
        void copy_name(const char *name)
        {
            name_ = new char[strlen(name) + 1];
            strcpy(name_, name);
        }

    private:
        char *name_; // Указатель владеет C-style строкой, на которую указывает.
        int quantity_;
        double price_;
    };

    std::ostream &operator<<(std::ostream &out, const Product &prod)
    {
        out << prod.name_ << " " << prod.quantity_ << " " << prod.price_;
        return out;
    }

    void print(const containers::my_vector<Product> &v)
    {
        std::cout << v << std::endl;
    }

} // namespace product

template <typename T>
void test_my_vector(T a, T b)
{
    std::cout << "test_my_vector" << '\n';
    containers::my_vector<T> v1;
    v1 = v1 = v1 = v1 = v1 = v1 = v1 = v1 = v1;
    v1.push_back(a);
    v1.push_back(b);
    v1.push_back(a);
    assert(v1.size() == 3);
    assert(!v1.empty());
    assert(v1.capacity() == 4);
    std::cout << "good: " << a << " " << b << " " << a << '\n';
    std::cout << "ours: " << v1 << "\n\n";
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    v1.push_back(a);
    v1.push_back(a);
    v1.push_back(a);
    assert(v1.size() == 3);
    assert(!v1.empty());
    assert(v1.capacity() == 4);
    std::cout << "good: " << a << " " << a << " " << a << '\n';
    std::cout << "ours: " << v1 << '\n';
    std::cout << "ours: " << v1[0] << " " << v1[1] << " " << v1[2] << "\n\n";
    v1.pop_back();
    assert(v1.size() == 2);
    assert(!v1.empty());
    assert(v1.capacity() == 4);
    containers::my_vector<T> v2 = v1;
    containers::my_vector<T> v3(v2);
    assert(v2.size() == 2);
    assert(!v2.empty());
    assert(v2.capacity() == 4);
    assert(v3.size() == 2);
    assert(!v3.empty());
    assert(v3.capacity() == 4);

    v2.pop_back();
    v2.push_back(a);
    v2.pop_back();
    v2.push_back(a);
    v2.pop_back();
    v2.push_back(a);
    v2.pop_back();
    v2.push_back(a);
    assert(v2.size() == 2);
    assert(!v2.empty());
    assert(v2.capacity() == 4);

    std::cout << "good: " << a << " " << a << '\n';
    std::cout << "ours: " << v2 << '\n';
    std::cout << "ours: " << v3 << "\n\n";
    v2.pop_back();
    v2.pop_back();
    assert(v2.size() == 0);
    assert(v2.empty());
    assert(v2.capacity() == 4);

    containers::my_vector<T> v4;
    assert(v4.size() == 0);
    assert(v4.empty());
    assert(v4.capacity() == 1);
    v4 = v3;
    v4 = v4;
    std::cout << "good: " << a << " " << a << '\n';
    std::cout << "ours: " << v4 << "\n\n";
    v4.clear();
    assert(v4.empty());
    v4.clear();
    assert(v4.empty());
    v4 = v4;
    assert(v4.empty());

    containers::my_vector<T> v5(v4);
    for (std::size_t i = 0; i < 100; ++i)
        v5.push_back(a);
    for (std::size_t i = 0; i < 100; ++i)
        v5.pop_back();
    for (std::size_t i = 0; i < 150; ++i)
        v5.push_back(b);
    for (std::size_t i = 0; i < 100; ++i)
        v5.pop_back();
    assert(v5.size() == 50);
    assert(v5.capacity() == 256);
}

template <typename T>
void test_my_vector_default_constructible(T a, T b)
{
    std::cout << "test_my_vector_default_constructible" << '\n';

    containers::my_vector<T> vec(10);
    assert(vec.size() == 10);
    assert(vec.capacity() == 16);
    assert(!vec.empty());
    for (std::size_t i = 0; i < vec.size(); ++i)
        assert(vec[i] == T());
    std::cout << "good: ";
    for (std::size_t i = 0; i < vec.size(); ++i)
        std::cout << T() << " ";
    std::cout << '\n';
    std::cout << "ours: " << vec << "\n\n";

    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    containers::my_vector<T> v1, v2(100);
    std::size_t real_cp1 = 1;
    std::size_t real_cp2 = 128;
    for (std::size_t i = 0; i < 1000; ++i)
    {
        std::size_t cur = rng() % 1000;
        while (real_cp1 < cur)
            real_cp1 <<= 1;
        while (real_cp2 < cur)
            real_cp2 <<= 1;
        if (i & 1)
        {
            v1.resize(cur);
            v2.resize(cur);
        }
        else
        {
            std::size_t size = v1.size();
            v1.reserve(cur);
            assert(v1.size() == size);

            size = v2.size();
            v2.reserve(cur);
            assert(v2.size() == size);
        }
        assert(v1.capacity() == real_cp1);
        assert(v2.capacity() == real_cp2);
    }
}

int main()
{
    test_my_vector<std::string>("snickers", "mars");
    test_my_vector<int>(5, 10);
    test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
    test_my_vector_default_constructible<int>(1, 2);
    test_my_vector_default_constructible<std::string>("snickers", "mars");
    return 0;
}
