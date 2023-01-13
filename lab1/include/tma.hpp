#ifndef TMA_HPP
#define TMA_HPP

#include <vector>
#include <type_traits>
#include <cassert>

template <typename T>
void tma(
  const std::vector< T >& a,
  const std::vector< T >& c,
  const std::vector< T >& b,
  std::vector< T >& x,
  const std::vector< T >& r
) {
  static_assert(std::is_floating_point< T >::value);
  assert(a.size() == b.size());
  assert(a.size() == c.size());
  assert(a.size() == x.size());
  assert(a.size() == r.size());

  size_t sz = r.size();
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