#ifndef TMA_HPP
#define TMA_HPP

#include <vector>
#include <cstddef>
#include <type_traits>
#include <cassert>

template <typename T = double>
void tma(
  const std::vector< T >& a,
  const std::vector< T >& c,
  const std::vector< T >& b,
        std::vector< T >& x,
  const std::vector< T >& r
) {
  static_assert(std::is_floating_point< T >::value);

  std::size_t sz = r.size();

  assert(sz == b.size());
  assert(sz == c.size());
  assert(sz == x.size());
  assert(sz == r.size());
  assert(a[0] == 0);
  assert(b[sz - 1] == 0);

  std::vector< T > y(sz);
  std::vector< T > p(sz);

  y[0] = b[0] / c[0];
  p[0] = r[0] / c[0];

  for( size_t i = 1; i < sz; i++)
  {
    y[i] = b[i] / (c[i] - a[i] * y[i - 1]);
    p[i] = ( r[i] - a[i] * p[i - 1] ) / ( c[i] - a[i] * y[i - 1] );
  }

  for (int i = sz - 1; i >= 0; i--)
  {
    x[i] = p[i] - y[i] * x[i + 1];
  }
}

#endif