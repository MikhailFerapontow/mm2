#ifndef BALANCE_HPP
#define BALANCE_HPP

#include <cstddef>
#include <vector>
#include <iterator>
#include <iostream>
#include <functional>

#include "utils/data.hpp"
#include "utils/balance_utils.hpp"
#include "tma.hpp"

template <typename T = double>
void balance_solve(std::size_t N, const Data< T >& data,
                std::vector< T >& balance_result, std::vector< T >& tma_result)
{
  static_assert(std::is_floating_point< T >::value);
  assert(data.R_L < data.R_R);
  
  std::vector< T > a(N + 1);
  std::vector< T > c(N + 1);
  std::vector< T > b(N + 1);
  std::vector< T > r(N + 1);

  init_balance(N, data, a, c, b, r, balance_result);

  tma(a, c, b, r, tma_result);

  std::copy(balance_result.begin(), balance_result.end(), std::ostream_iterator< T >(std::cout, " "));
  std::cout << "\n";
  std::copy(tma_result.begin(), tma_result.end(), std::ostream_iterator< T >(std::cout, " "));
};

#endif