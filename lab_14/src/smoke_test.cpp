#include "linq.hpp"
#include <math.h>
#include <assert.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>

using linq::from;

void example1()
{
  int xs[] = {1, 2, 3, 4, 5};

  std::vector<int> res =
      from(xs, xs + 5)                         // Взять элементы xs
          .select([](int x) { return x * x; }) // Возвести в квадрат
          .where_neq(25)                       // Оставить только значения != 25
          .where([](int x) { return x > 3; })  // Оставить только значения > 3
          .drop(2)                             // Убрать два элемента из начала
          .to_vector();                        // Преобразовать результат в вектор

  std::vector<int> expected = {16};
  assert(res == expected);
  std::cout << "example1 - AC\n";
}

void example2()
{
  std::stringstream ss("1 2 3 -1 4");
  std::istream_iterator<int> in(ss), eof;

  std::vector<int> res =
      from(in, eof)     // Взять числа из входного потока
          .take(4)      // Не более четырёх чисел
          .until_eq(-1) // Перестать читать после прочтения -1
          .to_vector(); // Получить список считанных чисел

  std::vector<int> expected = {1, 2, 3};
  assert(expected == res);

  int remaining;
  assert(ss >> remaining);
  assert(remaining == 4);
  std::cout << "example2 - AC\n";
}

void example3()
{
  int xs[] = {1, 2, 3, 4, 5};

  std::vector<double> res =
      from(xs, xs + 5)                                   // Взять элементы xs
          .select<double>([](int x) { return sqrt(x); }) // Извлечь корень
          .to_vector();                                  // Преобразовать результат в вектор

  assert(res.size() == 5);
  for (std::size_t i = 0; i < res.size(); i++)
  {
    assert(fabs(res[i] - sqrt(xs[i])) < 1e-9);
  }
  std::cout << "example3 - AC\n";
}

void example4()
{
  std::stringstream iss("4 16");
  std::stringstream oss;
  std::istream_iterator<int> in(iss), eof;
  std::ostream_iterator<double> out(oss, "\n");

  from(in, eof)                                                       // Взять числа из входного потока
      .select([](int x) { return static_cast<int>(sqrt(x) + 1e-6); }) // Извлечь из каждого корень
      .copy_to(out);                                                  // Вывести на экран

  assert(oss.str() == "2\n4\n");
  std::cout << "example4 - AC\n";
}

void from_to_vector()
{
  std::vector<int> xs = {1, 2, 3};
  std::vector<int> res = from(xs.begin(), xs.end()).to_vector();
  assert(res == xs);
  std::cout << "from_to_vector() - AC\n";
}

void from_select()
{
  const int xs[] = {1, 2, 3};
  std::vector<int> res = from(xs, xs + 3).select([](int x) { return x + 5; }).to_vector();
  std::vector<int> expected = {6, 7, 8};
  assert(res == expected);
  std::cout << "from_select() - AC\n";
}

void from_drop_select()
{
  const int xs[] = {1, 2, 3};
  std::vector<int> res = from(xs, xs + 3).drop(1).select([](int x) { return x + 5; }).to_vector();
  std::vector<int> expected = {7, 8};
  assert(res == expected);
  std::cout << "from_drop_select() - AC\n";
}

template <typename F>
class my_class
{
public:
  my_class(F &&f) : foo(std::move(f)) {}
  my_class &operator=(const my_class &other) = delete;
  my_class &operator=(my_class &other) = delete;
  my_class &operator=(my_class other) = delete;
  my_class(const my_class &other) = delete;
  bool operator()(int x) const
  {
    return foo(x);
  }

private:
  F &&foo;
};

template <typename F>
auto force_move(F &&f)
{
  return my_class<F>(std::move(f));
}

void non_copy()
{
  auto xs = std::vector<int>{9, 4, 8, 1, -3, 8, 7};
  auto f = force_move([](int x) { return x < 0; });
  auto res = from(xs.begin(), xs.end()).until(f).to_vector();
  auto res2 = from(xs.begin(), xs.end()).until(force_move([](int x) { return x < 0; })).to_vector();

  assert((std::vector<int>{9, 4, 8, 1}) == res);
  assert((std::vector<int>{9, 4, 8, 1}) == res2);
  std::cout << "non_copy() - AC\n";
}

void empty()
{
  auto xs = std::vector<int>{9, 4, 8, 1, -3, 8, 7};
  std::vector<int> res = from(xs.begin(), xs.begin()).select([](int x) { return x + 5; }).to_vector();
  assert(std::vector<int>{} == res);
  std::cout << "empty() - AC\n";
}

int main()
{
  from_to_vector();
  from_select();
  from_drop_select();
  example1();
  example2();
  example3();
  example4();
  non_copy();
  empty();
  return 0;
}
