#ifndef DATA_TABLE_HPP
#define DATA_TABLE_HPP

#include <cmath>
#include <vector>
#include "utils/data.hpp"

std::vector< Data< double > > get_data()
{
  std::vector< Data< double > > data_table =
  {
    {
      M_PI / 6, M_PI / 3,
      [](double r, double t) -> double { return r; }, //u
      [](double r, double t) -> double { return std::cos(r) / 2 + 3; },//k
      [](double r, double t) -> double { return std::sin(r) / 2 + 2; }, //q
      [](double r, double t) -> double {
         return (-std::cos(r) + r * std::sin(r) - 6 + r * r * std::sin(r) + 4 * r * r) / (2 * r);
      },
      [](double t) -> double { return std::sqrt(3) / 4 + 3; },
      [](double t) -> double { return 3.25; },
    },
  };

  return data_table;
}

#endif