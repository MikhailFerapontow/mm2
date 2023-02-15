#ifndef BALANCE_UTILS_HPP
#define BALANCE_UTILS_HPP

#include <vector>

#include "data.hpp"
#include "grid.hpp"

template <typename T = double>
void init_balance(
  std::size_t N,
  const Data< T >& data,
  std::vector< T >& a,
  std::vector< T >& c,
  std::vector< T >& b,
  std::vector< T >& r,
  std::vector< T >& x,
  T t
)
{
  static_assert(std::is_floating_point< T >::value);

  std::size_t sz = N + 1;
  assert(a.size() == sz);
  assert(c.size() == sz);
  assert(b.size() == sz);
  assert(r.size() == sz);

  auto nu_1 = data.nu_1;
  auto nu_2 = data.nu_2;

  auto h_1 = h1< T >(N, data);
  auto h_2 = h2< T >(N, data);

  auto r_1 = r1< T >(N, data);
  auto r_2 = r2< T >(N, data);

  auto k_1 = k1< T >(N, data);
  auto k_2 = k2< T >(N, data);

  auto q_1 = q< T >(N, data);
  auto f_1 = f< T >(N, data);

  double B1 = (r_2(0) * k_2(0, t)) / (h_1(1) * r_1(0) * h_2(0));
  double B2 = 0;

  a[0] = 0;
  c[0] = -(B1 + q_1(0, t));
  b[0] = B1;
  r[0] = nu_1 / h_2(0) + f_1(0, t);
  x[0] = data.u(r_1(0), t);

  for (int i = 1; i < N; i++)
  {
    B1 = (r_2(i) * k_2(i, t)) / (h_1(i + 1) * r_1(i) * h_2(i));
    B2 = (r_2(i - 1) * k_2(i - 1, t)) / (h_1(i) * r_1(i) * h_2(i));

    a[0] = B2;
    c[0] = -(B1 + B2 + q_1(i, t));
    b[0] = B1;
    r[0] = f_1(i, t);
    x[0] = data.u(r_1(i), t);
  }

  B2 = (r_2(N - 1) * k_2(N - 1, t)) / (h_1(N) * r_1(N) * h_2(N));

  a[N] = B2;
  c[N] = -(B2 + q_1(n, t));
  b[N] = 0;
  r[N] = nu_2 / h_2(N);
  x[N] = data.u(r_1(N), t)
}


template< typename T >
void init_solution(
  std::size_t N,
  const Data< T >& data,
  std::vector< T >& x,
  T t
)
{
  static_assert(std::is_floating_point< T >::value);

  auto r_1 = r1< T >(N, data);
  for (std::size_t i = 1; i <= N; i++)
  {
    x[i - 1] = data.u(r_1(i), t);
  }
}
#endif