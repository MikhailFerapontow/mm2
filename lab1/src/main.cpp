#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <algorithm>

#include "utils.hpp"
#include "tma.hpp"
#include "balance.hpp"
#include "data_table.hpp"

int main()
{
  auto data_table = get_data< float >();
  std::size_t N = 10;

  std::vector< float > first(N + 1);
  std::vector< float > second(N + 1);

  for (auto data : data_table)
  {
    balance_solve(N, data, first, second);
    
    std::cout << "\n eps = " << eps(first, second) << "\n";
  }

  // std::vector<double> a = { 0, -1, -1, -1 };
  // std::vector<double> c = { 4,  4,  4,  4 };
  // std::vector<double> b = {-1, -1, -1,  0 };
  // std::vector<double> r = { 5,  5, 10, 23 };
  // std::vector<double> x(4);

  // tma(a, c, b, r, x);

  // std::copy(x.begin(), x.end(), std::ostream_iterator< double >(std::cout, " "));
  // std::cout << "\n";

  // return 0;
}