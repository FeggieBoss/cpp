#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iostream>

namespace linq
{
  namespace impl
  {

    template <typename T, typename Iter>
    class range_enumerator;
    template <typename T>
    class drop_enumerator;
    template <typename T>
    class take_enumerator;
    template <typename T, typename U, typename F>
    class select_enumerator;
    template <typename T, typename F>
    class until_enumerator;
    template <typename T>
    class until_eq_enumerator;
    template <typename T, typename F>
    class where_enumerator;
    template <typename T>
    class where_neq_enumerator;

    template <typename T>
    class enumerator
    {
    public:
      virtual T &operator*() = 0;           // Получает текущий элемент.
      virtual void operator++() = 0;        // Переход к следующему элементу
      virtual explicit operator bool() = 0; // Возвращает true, если есть текущий элемент

      auto drop(int count)
      {
        return drop_enumerator<T>(*this, count);
      }

      auto take(int count)
      {
        return take_enumerator<T>(*this, count);
      }

      template <typename U = T, typename F>
      auto select(F &func)
      {
        return select_enumerator<U, T, F>(*this, func);
      }
      template <typename U = T, typename F>
      auto select(F &&func)
      {
        return select_enumerator<U, T, F>(*this, std::move(func));
      }

      template <typename F>
      auto until(F &func)
      {
        return until_enumerator<T, F>(*this, func);
      }
      template <typename F>
      auto until(F &&func)
      {
        return until_enumerator<T, F>(*this, std::move(func));
      }

      auto until_eq(T v)
      {
        return until_eq_enumerator<T>(*this, v);
      }

      template <typename F>
      auto where(F &predicate)
      {
        return where_enumerator<T, F>(*this, predicate);
      }
      template <typename F>
      auto where(F &&predicate)
      {
        return where_enumerator<T, F>(*this, std::move(predicate));
      }

      auto where_neq(T v)
      {
        return where_neq_enumerator<T>(*this, v);
      }

      std::vector<T> to_vector()
      {
        std::vector<T> v;
        while (operator bool())
        {
          v.push_back(this->operator*());
          this->operator++();
        }
        return v;
      }

      template <typename Iter>
      void copy_to(Iter it)
      {
        while (operator bool())
        {
          *(it++) = this->operator*();
          this->operator++();
        }
      }
    };

    template <typename T, typename Iter>
    class range_enumerator : public enumerator<T>
    {
    public:
      range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

      T &operator*() override
      {
        return const_cast<T &>(*begin_);
      }
      void operator++() override
      {
        ++begin_;
      }
      explicit operator bool() override
      {
        return begin_ != end_;
      }

    private:
      Iter begin_, end_;
    };

    template <typename T>
    class drop_enumerator : public enumerator<T>
    {
    public:
      drop_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

      T &operator*() override
      {
        skip();
        return *parent_;
      }
      void operator++() override
      {
        skip();
        ++parent_;
      }
      explicit operator bool() override
      {
        skip();
        return static_cast<bool>(parent_);
      }

    private:
      void skip()
      {
        while (bool(parent_) && count_)
        {
          ++parent_;
          --count_;
        }
      }

      enumerator<T> &parent_;
      int count_;
    };

    template <typename T>
    class take_enumerator : public enumerator<T>
    {
    public:
      take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

      T &operator*() override
      {
        return *parent_;
      }
      void operator++() override
      {
        ++parent_;
        --count_;
      }
      explicit operator bool() override
      {
        if (!static_cast<bool>(parent_))
          return false;
        return (count_ > 0);
      }

    private:
      enumerator<T> &parent_;
      int count_;
    };

    template <typename T, typename U, typename F>
    class select_enumerator : public enumerator<T>
    {
    public:
      select_enumerator(enumerator<U> &parent, F &&func) : parent_(parent), foo(std::move(func))
      {
        if (static_cast<bool>(parent_))
          mem = foo(*parent_);
      }
      select_enumerator(enumerator<U> &parent, F &func) : parent_(parent), foo(func)
      {
        if (static_cast<bool>(parent_))
          mem = foo(*parent_);
      }

      T &operator*() override
      {
        return mem;
      }
      void operator++() override
      {
        ++parent_;
        if (static_cast<bool>(parent_))
          mem = foo(*parent_);
      }
      explicit operator bool() override
      {
        return static_cast<bool>(parent_);
      }

    private:
      enumerator<U> &parent_;
      const F &foo;
      T mem;
    };

    template <typename T, typename F>
    class until_enumerator : public enumerator<T>
    {
    public:
      until_enumerator(enumerator<T> &parent, F &&predicate) : parent_(parent), p(std::move(predicate)) {}
      until_enumerator(enumerator<T> &parent, F &predicate) : parent_(parent), p(predicate) {}

      T &operator*() override
      {
        return *parent_;
      }
      void operator++() override
      {
        ++parent_;
      }
      explicit operator bool() override
      {
        if (!static_cast<bool>(parent_))
          return false;
        return !p(*parent_);
      }

    private:
      enumerator<T> &parent_;
      const F &p;
    };

    template <typename T>
    class until_eq_enumerator : public enumerator<T>
    {
    public:
      until_eq_enumerator(enumerator<T> &parent, T v) : parent_(parent), el(std::move(v)) {}

      T &operator*() override
      {
        return *parent_;
      }
      void operator++() override
      {
        ++parent_;
      }
      explicit operator bool() override
      {
        if (!static_cast<bool>(parent_))
          return false;
        return (*parent_ != el);
      }

    private:
      enumerator<T> &parent_;
      T el;
    };

    template <typename T, typename F>
    class where_enumerator : public enumerator<T>
    {
    public:
      where_enumerator(enumerator<T> &parent, F &&predicate) : parent_(parent), p(std::move(predicate)) {}
      where_enumerator(enumerator<T> &parent, F &predicate) : parent_(parent), p(predicate) {}

      T &operator*() override
      {
        skip_bad_prefix();
        return *parent_;
      }
      void operator++() override
      {
        skip_bad_prefix();
        ++parent_;
        while (static_cast<bool>(parent_) && !p(*parent_))
          ++parent_;
      }
      explicit operator bool() override
      {
        skip_bad_prefix();
        return static_cast<bool>(parent_);
      }

    private:
      enumerator<T> &parent_;
      const F &p;

    private:
      bool BAD_PREFIX = true;
      void skip_bad_prefix()
      {
        if (!BAD_PREFIX)
          return;
        BAD_PREFIX = false;

        while (static_cast<bool>(parent_) && !p(*parent_))
          ++parent_;
      }
    };
    template <typename T>
    class where_neq_enumerator : public enumerator<T>
    {
    public:
      where_neq_enumerator(enumerator<T> &parent, T v) : parent_(parent), el(std::move(v)) {}

      T &operator*() override
      {
        skip_bad_prefix();
        return *parent_;
      }
      void operator++() override
      {
        skip_bad_prefix();
        ++parent_;
        while (static_cast<bool>(parent_) && (*parent_ == el))
          ++parent_;
      }
      explicit operator bool() override
      {
        skip_bad_prefix();
        return static_cast<bool>(parent_);
      }

    private:
      enumerator<T> &parent_;
      T el;

    private:
      bool BAD_PREFIX = true;
      void skip_bad_prefix()
      {
        if (!BAD_PREFIX)
          return;
        BAD_PREFIX = false;

        while (static_cast<bool>(parent_) && (*parent_ == el))
          ++parent_;
      }
    };

  } // namespace impl

  template <typename Iter>
  auto from(Iter begin, Iter end)
  {
    return impl::range_enumerator<typename std::iterator_traits<Iter>::value_type, Iter>(begin, end);
  }

} // namespace linq

#endif // LINQ_H_
