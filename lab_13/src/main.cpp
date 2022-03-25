#include <cstddef>
#include "my_array.h"
#include <chrono>
#include <random>
#include <iostream>

using lab_13::my_array;

template <typename T, std::size_t N>
void test_core()
{
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    assert(!a.empty());
    assert(!ca.empty());
    assert(a.size() == N);
    assert(ca.size() == N);

    a.at(0);
    ca.at(0);
    a[0];
    ca[0];
    (void)static_cast<const T &>(a[0]);
    (void)static_cast<const T &>(ca[0]);
}

template <typename T, std::size_t N>
void test_assign()
{
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.fill(T());

    assert(a[0] == T());
    a[0] = T();
    a[0] = a[0];
    a[0] = ca[0];
    a[1] = a[1] = a[0] = a[5] = T();
}

template <std::size_t N>
void my_test()
{
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    my_array<bool, N> a;

    // check size
    assert(sizeof(a) == ((N + 7) / 8));

    // check fill
    a.fill(0);
    for (std::size_t i = 0; i < N; ++i)
    {
        //std::cout<<a[i]<<"\n";
        assert(a[i] == 0);
    }
    a.fill(1);
    for (std::size_t i = 0; i < N; ++i)
    {
        //std::cout<<a[i]<<"\n";
        assert(a[i] == 1);
    }
    a.fill(1);
    for (std::size_t i = 0; i < N; ++i)
        assert(a[i] == 1);

    // check [] and =
    for (std::size_t i = 0; i < 1000; ++i)
    {
        bool cur = rng() % 2;
        std::size_t index1 = rng() % N;
        std::size_t index2 = rng() % N;

        // my_array[i] = x
        a[index1] = cur;
        assert(a[index1] == cur);

        // my_array[i] = my_array[j]
        a[index2] = a[index1];
        assert(a[index2] == cur);
        assert(a[index2] == a[index1]);

        // my_array[i] = my_array[i]
        a[0] = a[0];
        assert(a[0] == a[0]);

        // x = my_array[i]
        bool x = a[index1];
        assert(x == a[index1]);
        assert(x == a[index2]);

        // at()
        a.at(index1);
    }

    // =
    a[6] = a[6] = a[6] = a[1] = a[1] = a[2];
    a[7] = a[1] = a[7] = a[2] = a[7] = a[4] = 0;
    a[1] = a[2] = a[3] = a[5] = a[6] = a[9] = 1;

    // empty / size
    assert(!a.empty());
    assert(a.size()==N);
    
    std::cout<<"OK\n";
}

class NonCopyable
{
public:
    NonCopyable() {}

private:
    NonCopyable(const NonCopyable &);
    NonCopyable &operator=(const NonCopyable);
};

int main()
{
    test_core<int, 10>();
    test_core<bool, 10>();
    test_core<NonCopyable, 10>();

    test_assign<int, 10>();
    test_assign<bool, 10>();

    my_test<100>();
    my_test<66>();
    my_test<777>();
}