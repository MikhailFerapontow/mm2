#include "euler.hpp"

#include "utils/balance_utils.hpp"
#include "utils.hpp"
#include "tma.hpp"

double forward_euler(
  std::size_t N, double t, double H,
  const Data< double >& data,
  const std::vector< double >& prev,
  std::vector< double >& next
)
{
  std::vector< double > a(N);
  std::vector< double > c(N);
  std::vector< double > b(N);
  std::vector< double > r(N);
  std::vector< double > x(N);

  std::vector< double > rez(N);

  init_balance(N, data, a, c, b, r, x, t);
  init_solution(N, data, x, t + H);

  for(int i = 0; i < N; i++)
  {
    a[i] *= H;
    c[i] = 1 + H * c[i];
    b[i] *= H;
    r[i] *= H;
  }

  multiply(a, c, b, prev, next);
  add(next, r, next);
  return eps(x, next);
}

double backward_euler(
  std::size_t N, double t, double H,
  const Data< double >& data,
  const std::vector< double >& prev,
  std::vector< double >& next
)
{
  std::vector< double > a(N);
  std::vector< double > c(N);
  std::vector< double > b(N);
  std::vector< double > r(N);
  std::vector< double > x(N);

  std::vector< double > rez(N);

  init_balance(N, data, a, c, b, r, x, t);
  init_solution(N, data, x, t + H);

  for (int i = 0; i < N; i++)
  {
    a[i] *= -H;
    c[i] = 1 - H * c[i];
    b[i] *= -H;
    r[i] *= H;
  }

  add(r, prev, r);
  tma(a, c, b, r, next);
  return eps(x, next);
}
