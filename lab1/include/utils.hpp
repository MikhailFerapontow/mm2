#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <iomanip>
#include <cmath>

#include <boost/range/combine.hpp>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

template< typename T >
T eps(const std::vector< T > &v1,
             const std::vector< T > &v2)
{
  T eps_ = 0;

  for (auto &&tuple: boost::combine(v1, v2))
  {
  T x1, x2;
  boost::tie(x1, x2) = tuple;

  T del = std::fabs(x1 - x2);

    if (del > eps_)
    {
      eps_ = del;
    }
  }

  return eps_;
}

template <typename T>
T cond(
  const std::vector< T >& a,
  const std::vector< T >& c,
  const std::vector< T >& b
)
{
  std::size_t N = b.size() - 1;
  double rez = 1;

  gsl_matrix* m = gsl_matrix_alloc(N + 1, N + 1);
  gsl_matrix* n = gsl_matrix_alloc(N + 1, N + 1);

  gsl_matrix_set_zero(m);

  gsl_matrix_set(m, 0, 0, c[0]);
  gsl_matrix_set(m, 0, 1, b[0]);

  for (std::size_t i = 1; i < N; i++)
  {
    gsl_matrix_set(m, i, i - 1, a[i]);
    gsl_matrix_set(m, i, i, c[i]);
    gsl_matrix_set(m, i, i + 1, b[i]);
  }

  gsl_matrix_set(m, N, N - 1, a[N]);
  gsl_matrix_set(m, N, N, c[N]);

  rez *= gsl_matrix_norm1(m);

  int s;
  gsl_permutation* p = gsl_permutation_alloc(c.size());

  gsl_linalg_LU_decomp(m, p, &s);
  gsl_linalg_LU_invert(m, p, n);

  rez *= gsl_matrix_norm1(n);

  gsl_permutation_free(p);
  gsl_matrix_free(m);
  gsl_matrix_free(n);

  return rez;
}


#endif