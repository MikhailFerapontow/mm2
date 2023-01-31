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
  auto data_table2 = get_data< double >();

  std::size_t N = 512;

    std::vector< float > first(N + 1);
    std::vector< float > second(N + 1);
    std::cout << "N = " << N << "\n";
    for (auto data : data_table)
    {
      balance_solve(N, data, first, second);
      
      std::cout << "eps = " << eps(first, second) << "\n";
    }


  // for (std::size_t N = 4; N <= 2048; N *= 2)
  // {
  //   std::vector< double > first(N + 1);
  //   std::vector< double > second(N + 1);
  //   std::cout << "N = " << N << "\n";
  //   for (auto data : data_table2)
  //   {
  //     balance_solve(N, data, first, second);

  //     std::cout << "eps = " << eps(first, second) << "\n";
  //   }
  // }

  return 0;
}