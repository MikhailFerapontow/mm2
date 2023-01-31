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
  };

  return data_table;
}

#endif