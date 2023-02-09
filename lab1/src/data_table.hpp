#ifndef DATA_TABLE_HPP
#define DATA_TABLE_HPP

#include <cmath>
#include <vector>
#include "utils/data.hpp"

template <typename T = double>
std::vector< Data< T > > get_data()
{
  std::vector< Data< T > > data_table =
  {
    {
      1, 2,
      [](T r) -> T { return 2 * r + 3; },
      [](T r) -> T { return r; },
      [](T r) -> T { return 1; },
      [](T r) -> T { return 2 * r - 1; },
      -2, 4
    },
    {
      1, 2,
      [](T r) -> T { return 2 * std::pow(r, 2) + 3; },
      [](T r) -> T { return std::pow(r, 2); },
      [](T r) -> T { return 1; },
      [](T r) -> T { return -14 * std::pow(r, 2) + 3; },
      -4, 32
    },
    {
      1, 2,
      [](T r) -> T { return 2 * std::pow(r, 3) + 3; },
      [](T r) -> T { return std::pow(r, 3); },
      [](T r) -> T { return 1; },
      [](T r) -> T { return -36 * std::pow(r, 4) + 2 * std::pow(r, 3) + 3; },
      -6, 192
    },
    {
      M_PI / 6, M_PI / 3,
      [](T r) -> T { return std::sin(r); }, //u
      [](T r) -> T { return std::log(r) / r; },//k
      [](T r) -> T { return std::cos(r); }, //q
      [](T r) -> T {
         return ((-std::cos(r) + r * std::log(r) * std::sin(r)) / std::pow(r, 2) ) + std::cos(r) * std::sin(r);
      },
      -std::log(M_PI / 6) * 3 * std::sqrt(3) / M_PI, 3 * std::log(M_PI / 3) / (2 * M_PI)
    },
  };

  return data_table;
}

#endif