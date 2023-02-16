#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <initializer_list>

#include "utils/balance_utils.hpp"
#include "data_table.hpp"
#include "euler.hpp"

int main()
{
  std::size_t N = 16;

  auto data_table = get_data();

  std::cout << std::scientific;
  std::cout << "forward\n";
  for(auto&& H : {1e-1, 1e-2, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6})
  {
    double t0 = 0;
    std::cout << std::setprecision(0) << H << " ";
    std::vector< double > first(N + 1);
    std::vector< double > final(N + 1);

    for (auto&& data : data_table)
    {
      init_solution(N, data, first, t0);
      forward_euler(N, t0, H, data, first, final);

      double x = 0;
      for(double t = t0 + H; t < 1; t += H)
      {
        first.swap(final);

        double eps = forward_euler(N, t, H, data, first, final);
        x = (eps > x ? eps : x);
      }

      std::cout << std::setw(10) << std::setprecision(2) << x << " ";
    }
    std::cout << "\n";
  }


  std::cout << "backward\n";
  for(auto&& H : {1e-1, 1e-2, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6})
  {
    double t0 = 0;
    std::cout << std::setprecision(0) << H << " ";

    std::vector< double > first(N + 1);
    std::vector< double > final(N + 1);

    for (auto&& data : data_table)
    {
      init_solution(N, data, first, t0);
      backward_euler(N, t0, H, data, first, final);

      double x = 0;
      for(double t = t0 + H; t < 1; t += H)
      {
        first.swap(final);

        double eps = backward_euler(N, t, H, data, first, final);
        x = (eps > x ? eps : x);
      }

      std::cout << std::setw(10) << std::setprecision(2) << x << " ";
    }
    std::cout << "\n";
  }
  return 0;
}