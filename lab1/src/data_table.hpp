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
      M_PI, 3 * M_PI / 2,
      [](T r) -> T { return std::sin(r); },
      [](T r) -> T { return std::cos(r); },
      [](T r) -> T { return std::tan(r); },
      [](T r) -> T {
         return - std::pow(std::cos(r), 2) / r + sin(2 * r) + std::pow(std::sin(r), 2) / std::cos(r) ;
      },
      -1, 0
    },
  };

  return data_table;
}

#endif