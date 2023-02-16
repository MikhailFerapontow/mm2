#ifndef GRID_HPP
#define GRID_HPP

#include <cstddef>
#include <iostream>
#include <cassert>
#include "data.hpp"

template <typename T = double>
class h1
{
  public:
    h1(std::size_t N, const Data< T >& data):
      N_(N),
      data_(data)
    {}

    T operator() (std::size_t i)
    {
      assert(i > 0);
      assert(i <= N_);
      auto R_L = data_.R_L;
      auto R_R = data_.R_R;

      return (R_R - R_L) / N_;
    }

  private:
    std::size_t N_;
    const Data< T >& data_;
};

template <typename T = double>
class h2
{
  public:
    h2(std::size_t N, const Data< T >& data):
      N_(N),
      data_(data)
    {}

    T operator() (std::size_t i)
    {
      assert(i >= 0);
      assert(i <= N_);

      auto h_1 = h1(N_, data_);

      if (i == 0)
      {
        return h_1(i + 1) / 2;
      }

      if (i == N_)
      {
        return h_1(i) / 2;
      }

      return (h_1(i) + h_1(i + 1)) / 2;
    }

  private:
    std::size_t N_;
    const Data< T >& data_;
};

template <typename T = double>
class r1
{
  public:
    r1(std::size_t N, const Data<T>& data):
      N_(N),
      data_(data)
    {}

    T operator() (std::size_t i)
    {
      auto h_1 = h1(N_, data_);
      auto R_L = data_.R_L;

      auto r = R_L;

      for (int j = 1; j <= i; j++)
      {
        r += h_1(j);
      }

      return r;
    }
  private:
    std::size_t N_;
    const Data< T >& data_;
};


template <typename T = double>
class r2
{
  public:
    r2(std::size_t N, const Data< T >& data):
      N_(N),
      data_(data)
    {}

    T operator() (std::size_t i)
    {
      auto h_2 = h2(N_, data_);
      auto R_L = data_.R_L;

      auto r = R_L;

      for (int j = 0; j <= i; j++)
      {
        r += h_2(j);
      }

      return r;
    }
  private:
    std::size_t N_;
    const Data< T >& data_;
};

template <typename T = double>
class k1
{
  public:
    k1(std::size_t N, const Data< T > data):
      N_(N),
      data_(data)
    {}

    T operator() (std::size_t i, T t)
    {
      auto r_1 = r1(N_, data_);

      auto r = r_1(i);
      return data_.k(r, t);
    }

  private:
    std::size_t N_;
    const Data< T >& data_;
};

template <typename T = double>
class k2
{
  public:
    k2(std::size_t N, const Data< T >& data):
      N_(N),
      data_(data)
    {}

    T operator() (std::size_t i, T t)
    {
      auto r_2 = r2(N_, data_);
      auto r = r_2(i);
      return data_.k(r, t);
    }

  private:
    size_t N_;
    const Data< T >& data_;
};

template <typename T = double>
class q
{
  public:
    q(std::size_t N, const Data< T >& data):
      N_(N),
      data_(data)
    {}

    T operator() (std::size_t i, T t)
    {
      auto r_1 = r1(N_, data_);
      auto r = r_1(i);

      return data_.q(r, t);
    }

  private:
    std::size_t N_;
    const Data< T >& data_;
};

template <typename T = double>
class f
{
  public:
    f(std::size_t N, const Data< T >& data):
      N_(N),
      data_(data)
    {}

    T operator() (std::size_t i, T t)
    {
      auto r_1 = r1(N_, data_);
      auto r = r_1(i);

      return data_.f(r, t);
    }

  private:
    std::size_t N_;
    const Data< T >& data_;
};

#endif