#ifndef EULER_HPP
#define EULER_HPP

#include <cstddef>
#include <vector>
#include "utils/data.hpp"

double forward_euler(
  std::size_t N, double t, double H,
  const Data< double >& data,
  const std::vector< double >& prev,
  std::vector< double >& next
);

double backward_euler(
  std::size_t N, double t, double H,
  const Data< double >& data,
  const std::vector< double >& prev,
  std::vector< double >& next
);

#endif