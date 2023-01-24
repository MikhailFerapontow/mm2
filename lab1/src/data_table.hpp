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
      0, 10,
      [](T r) -> T { return 1; },
      [](T r) -> T { return 1; },
      [](T r) -> T { return 1; },
      [](T r) -> T { return 1; },
      1, 0
    },
  };

  return data_table;
}

#endif