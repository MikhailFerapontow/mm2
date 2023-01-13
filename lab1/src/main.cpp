#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <algorithm>

#include "../include/tma.hpp"

double R_L = 1;
double R_R = 4;
double N = 4;
double v1 = 1;
double v2 = 1;


double k(double r);
double q(double r);
double f(double r);
double u(double r);
double r(int i);
double r(double i);
double h(int i);
double hbar(int i);

int main()
{
  /*  std::vector<double> a = { 0, -1, -1, -1 };
  std::vector<double> c = { 4,  4,  4,  4 };
  std::vector<double> b = {-1, -1, -1,  0 };
  std::vector<double> r = { 5,  5, 10, 23 };
  std::vector<double> x(4);

  tma(a, c, b, x, r);

  std::copy(x.begin(), x.end(), std::ostream_iterator< double >(std::cout, " "));
  std::cout << "\n";*/

  std::vector<double> a(N);
  std::vector<double> c(N);
  std::vector<double> b(N);
  std::vector<double> g(N);
  std::vector<double> x(N);

  a[0] = 0;
  c[0] = r(0, 0.5) * k(0.5) / h(1) - hbar(0) * r(0) * q(0);
  b[0] = r(0, 0.5) * k(0.5) / h(1);
  g[0] = hbar(0) * r(0) * f(0) + r(0) * (-v1);

  for (int i = 1; i < N; i++)
  {
    a[i] = -r(i, -0.5) * k(i - 0.5) / h(i);
    c[i] = r(i, -0.5) * k(i -0.5) / h(i)
           + r(i, +0.5) * k(i + 0.5) / h(i + 1)
           + hbar(i) * r(i) * q(i);
    b[i] = -r(i, +0.5) * k(i + 0.5) / h(i + 1);
    g[i] = hbar(i) * r(i) * f(i);
  }

  a[N] = -r(N - 0.5) * k(N - 0.5) / h(N);
  c[N] = r(N - 0.5) * k(N - 0.5) / h(N) + hbar(N) * r(N) * q(N);
  g[N] = hbar(N) * r(N) * f(N) - r(N) * (-v2);

  return 0;
}

double k(double r)
{
  return 1.0;
}

double q(double r)
{
  return 1.0;
}

double f(double r)
{
  return 1.0;
}

double u(double r)
{
  return std::sin(r);
}

double r(int i)
{
  return R_L + h(i) * i;
}

double r(int i, double offset)
{
  if (offset < 0)
  {
    return (r(i) - r(i - 1)) / 2;
  }
  else if (offset > 0)
  {
    return (r(i + 1) - r(i)) / 2;
  }

  return -1.0;
}

double h(int i)
{
  double step = R_R - R_L;
  step /= N;

  return step;
}

double hbar(int i)
{
  if (i == 0)
  {
    return h(i + 1) / 2;
  }
  else if ( i > 0 && i < N)
  {
    return ( h(i) + h(i + 1) ) / 2;
  }
  else if (i == N)
  {
    return h(i) / 2;
  }

  return -1.0;
}