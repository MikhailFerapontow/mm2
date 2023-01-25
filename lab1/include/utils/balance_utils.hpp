#ifndef BALANCE_UTILS_HPP
#define BALANCE_UTILS_HPP

#include <vector>
#include <iostream>
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
  std::vector< T >& x
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

  // std::cout << "nu_1 = " << nu_1 << "; nu_2 = " << nu_2 << "\n";

  // std::cout << "h_1 = " << h_1(1) << "\n";
  // std::cout << "h_2 i=0 " << h_2(0) << "\n";
  // std::cout << "h_2 i=1..N-1 " << h_2(1) << ", " << h_2(N-2) << ", " << h_2(N-1) << "\n";
  // std::cout << "h_2 i=N " << h_2(N) << "\n";

  // for (int i = 1; i <= N; i++)
  // {
  //   std::cout << "r_1 ("<< i <<") = " << r_1(i) << "\n";
  // }

  // for (int i = 0; i <= N; i++)
  // {
  //   std::cout << "r_2 ("<< i <<") = " << r_2(i) << "\n";
  // }

  // std::cout << "k1 = " << k_1(r_2(2)) << " k2 =" << k_2(r_2(2)) << "\n";
  // std::cout << "q = " << q_1(r_2(2)) << "\n";
  // std::cout << "f_1 = " << f_1(r_2(2)) << "\n";

  //тут непонятки
  a[0] = 0;
  c[0] = r_2(1) * k_2(r_2(1)) / h_1(1) + h_2(0) * r_2(0) * q_1(0);
  b[0] = -r_2(1) * k_2(r_2(1)) / h_1(1);
  r[0] = h_2(0) * r_2(0) * f_1(0) + r_1(0) * (-nu_1);
  x[0] = data.u(r_1(0));

  for (int i = 1; i < N; i++)
  {
    a[i] = -r_2(i-1) * k_2(r_2(i-1)) / h_1(i);
    c[i] = r_2(i-1) * k_2(r_2(i-1)) / h_1(i) + r_2(i) * k_2(r_2(i)) / h_1(i + 1) + h_2(i) * r_1(i) * q_1(i);
    b[i] = -r_2(i + 1) * k_2(r_2(i + 1)) / h_1(i + 1);
    r[i] = h_2(i) * r_1(i) * f_1(i);
    x[i] = data.u(r_1(i));
  }

  a[N] = -r_2(N-1) * k_2(r_2(N-1)) / h_1(N);
  c[N] = r_2(N-1) * k_2(r_2(N-1)) / h_1(N) + h_2(N) * r_1(N) * q_1(N);
  r[N] = h_2(N) * r_1(N) * q_1(N) + r_1(N) * (-nu_2);
  x[N] = data.u(r_1(N));
}

#endif