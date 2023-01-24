#ifndef BALANCE_HPP
#define BALANCE_HPP

#include <cstddef>
#include <vector>
#include "utils/data.hpp"
#include "utils/balance_utils.hpp"

template <typename T = double>
T balance_solve(std::size_t N, const Data< T >& data)
{
  static_assert(std::is_floating_point< T >::value);
  assert(data.R_L < data.R_R);
  
  std::vector< T > a(N + 1);
  std::vector< T > c(N + 1);
  std::vector< T > b(N + 1);
  std::vector< T > r(N + 1);
  std::vector< T > x(N + 1);

  init_balance(N, data, a, c, b, r, x);

  return 1.0;
};

#endif