#ifndef EULER_HPP
#define EULER_HPP

#include <cstddef>
#include <vector>
#include <iostream>
#include "utils/data.hpp"
#include "utils/balance_utils.hpp"
#include "utils.hpp"
#include "tma.hpp"

template <typename T = double>
double forward_euler(
  std::size_t N, T t, T H,
  const Data< T >& data,
  const std::vector< T >& prev,
  std::vector< T >& next
)
{
  std::vector< T > a(N + 1);
  std::vector< T > c(N + 1);
  std::vector< T > b(N + 1);
  std::vector< T > r(N + 1);
  std::vector< T > x(N + 1);

  std::vector< T > rez(N + 1);

  init_balance(N, data, a, c, b, r, x, t);
  init_solution(N, data, x, t + H);

  for(int i = 0; i <= N; i++)
  {
    a[i] *= H;
    c[i] = 1 + H * c[i];
    b[i] *= H;
    r[i] *= H;
  }

  multiply(a, c, b, prev, next);
  add(next, r, next);
  return eps(x, next);
}

template <typename T = double>
double backward_euler(
  std::size_t N, T t, T H,
  const Data< T >& data,
  const std::vector< T >& prev,
  std::vector< T >& next
)
{
  std::vector< T > a(N + 1);
  std::vector< T > c(N + 1);
  std::vector< T > b(N + 1);
  std::vector< T > r(N + 1);
  std::vector< T > x(N + 1);

  std::vector< T > rez(N + 1);

  init_balance(N, data, a, c, b, r, x, t);
  init_solution(N, data, x, t + H);

  for (int i = 0; i <= N; i++)
  {
    a[i] *= -H;
    c[i] = 1 - H * c[i];
    b[i] *= -H;
    r[i] *= H;
  }

  add(r, prev, r);
  tma(a, c, b, r, next);
  return eps(x, next);
}

#endif