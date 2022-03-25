#ifndef LAB_13_ARRAY_H
#define LAB_13_ARRAY_H

#include <cassert>
#include <cstddef>

namespace lab_13
{
    const std::size_t block_size = 8;

    template <typename T, std::size_t N>
    class my_array
    {
    private:
        T array_[N];

    public:
        const T &at(std::size_t index) const
        {
            assert("Array index out of bounds" && index >= 0 && index < N);
            return array_[index];
        }
        const T &operator[](std::size_t index) const
        {
            return array_[index];
        }
        T &operator[](std::size_t index)
        {
            return array_[index];
        }

        bool empty() const
        {
            return (N == 0);
        }
        std::size_t size() const
        {
            return N;
        }

        void fill(const T &val)
        {
            for (std::size_t i = 0; i < N; ++i)
                array_[i] = val;
        }
    };

    template <std::size_t N>
    class my_array<bool, N>
    {
        typedef unsigned char _Block;

    private:
        _Block array_[(N + block_size - 1) / block_size]{'0'};

    private:
        static std::size_t to_int(_Block b)
        {
            return b - '0';
        }
        static std::size_t to_Block(std::size_t val)
        {
            return val + '0';
        }
        static _Block _G_maskbit(std::size_t block_pos)
        {
            return (_Block)((1 << block_pos) + '0');
        }
        _Block &_G_block(std::size_t index)
        {
            return array_[index / block_size];
        }
        const _Block &_G_block_val(std::size_t index) const
        {
            return array_[index / block_size];
        }
        bool _G_bit(std::size_t index) const
        {
            return (to_int(_G_block_val(index)) & to_int(_G_maskbit(index % block_size))) != 0;
        }

        class reference
        {
            friend class my_array<double, N>;

        private:
            _Block &_it;
            _Block _maskbit;

        public:
            reference(_Block &it, _Block maskbit) : _it(it),
                                                    _maskbit(maskbit) {}

            // my_array[i] = x
            reference &operator=(bool x)
            {
                if (x)
                    _it = to_Block((to_int(_it) | to_int(_maskbit)));
                else
                    _it = to_Block((to_int(_it) & ~(to_int(_maskbit))));

                return *this;
            }
            // my_array[i] = my_array[j]
            reference &operator=(const reference &j)
            {
                if ((to_int(j._it) & to_int(j._maskbit)) != 0)
                    _it = to_Block((to_int(_it) | to_int(_maskbit)));
                else
                    _it = to_Block((to_int(_it) & ~(to_int(_maskbit))));

                return *this;
            }
            // x = my_array[i]
            operator bool() const
            {
                return (to_int(_it) & to_int(_maskbit)) != 0;
            }
        };
        friend class block;

        reference _G_ref(std::size_t index)
        {
            return reference(_G_block(index / block_size), _G_maskbit((int)(index % block_size)));
        }

    public:
        const bool at(std::size_t index) const
        {
            assert("Array index out of bounds" && index >= 0 && index < N);
            return _G_bit(index);
        }
        const bool operator[](std::size_t index) const
        {
            return _G_bit(index);
        }
        reference operator[](std::size_t index)
        {
            return _G_ref(index);
        }

        bool empty() const
        {
            return (N == 0);
        }
        std::size_t size() const
        {
            return N;
        }

        void fill(bool val)
        {
            for (std::size_t i = 0; i < N; ++i)
                _G_ref(i) = val;
        }
    };

} // lab_13

#endif // LAB_13_ARRAY_H