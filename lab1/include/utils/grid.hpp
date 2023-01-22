#ifndef GRID_HPP
#define GRID_HPP

#include <cstddef>

template <typename T = double>
class Data;

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

      return (R_R - R_R) / N_;
    }

  private:
    std::size_t N_;
    const Data< T > data_;
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
      assert(i <= N);

      auto h_1 = h1(N, data);

      if (i == 0)
      {
        return h_1(i + 1) / 2
      }

      if (i == N_)
      {
        return h_1(i) / 2;
      }

      return (h_1(i) + h_1(i + 1)) / 2;
    }
  private:
    std::size_t N_;
    const Data< T > data_;
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
      assert(i >= 0);
      assert(i <= N);

      auto h_1 = h1(N_, data_);
      auto R_L = data_.R_L;

      return R_L + h_1(i) * i;
    }
  private:
    std::size_t N_;
    const Data< T > data_;
};


template <typename T = double>
class r2
{
  public:
    r2(std::size_t N, const Data< T > data):
      N_(N),
      data_(data_)
    {}

    T operator() (std::size_t i)
    {
      assert(i > 0);
      assert(i <= N);

      auto h_2 = h2(N_, data_);
      auto R_L = data_.R_L;

      for (std::size_t j = 0; j <= i; j ++)
      {
        R_L += h_2(j);
      }

      return R_L;
    }
  private:
    std::size_t N_;
    const Data< T > data_;
};

template <typename T = double>
class k1
{
  public:
    k1(std::size_t N, const Data< T > data):
      N_(N),
      data_(data)
    {}

    T operator() (std::size_t i)
    {
      auto r_1 = r1(N_, data_);

      auto r = r_1(i);
      return data_.k(r);
    }

  private:
    std::size_t N_;
    const Data< T > data_;
};

template <typename T = double>
class k2
{
  public:
    k2(std::size_t N, const Data< T > data):
      N_(N),
      data_(data)
    {}

    T operator() (std::size_t i)
    {
      auto r_2 = r2(N_, data_);
      auto r = r_2(i);

      return data_.k(r);
    }

  private:
    size_t N_;
    const Data< T > data_;
};

template <typename T = double>
class q
{
  public:
    q(std::size_t N, const Data< T > data):
      N_(N),
      data_(data_)
    {}

    T operator() (std::size_t i)
    {
      auto r_1 = r1(N_, data_);
      auto r = r_1(i);

      return data_.q(r);
    }

  private:
    std::size_t N_;
    const Data< T > data_;
};

template <typename T = double>
class f
{
  public:
    f(std::size_t N, const Data< T > data):
      N_(N),
      data_(data_)
    {}

    T operator() (std::size_t i)
    {
      auto r_1 = r1(N_, data_);
      auto r = r_1(i);

      return data_.f(r);
    }

  private:
    std::size_t N_;
    const Data< T > data_;
};

#endif