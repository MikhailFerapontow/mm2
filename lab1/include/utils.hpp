#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

#include <boost/range/combine.hpp>

template< typename T >
T eps(const std::vector< T > &v1,
             const std::vector< T > &v2)
{
  T eps_ = 0;

  for (auto &&tuple: boost::combine(v1, v2))
  {
  T x1, x2;
  boost::tie(x1, x2) = tuple;

  T del = std::fabs(x1 - x2);

    if (del > eps_)
    {
      eps_ = del;
    }
  }

  return eps_;
}

#endif