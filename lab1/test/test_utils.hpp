#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <cstddef>
#include <random>
#include <functional>
#include <vector>
#include <type_traits>

#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/join.hpp>

#include "tma.hpp"
#include "utils.hpp"

constexpr std::size_t MATRIX_SIZE = 100;
constexpr std::size_t NUM_ITER = 10000;

template <typename T = double>
void init_test_data(
  std::vector< T >& a,
  std::vector< T >& c,
  std::vector< T >& b,
  std::vector< T >& r,
  std::vector< T >& x
)
{
  static_assert(std::is_floating_point< T >::value);

  std::size_t sz = x.size();

  assert(sz == a.size());
  assert(sz == c.size());
  assert(sz == b.size());
  assert(sz == r.size());

  std::random_device rd;
  std::mt19937 eng(rd());
  std::uniform_real_distribution dist(-10.0, 10.0);
  auto gen = std::bind(dist, eng);

  auto j_range = boost::join(
    boost::join(
      boost::make_iterator_range(a.begin(), a.end()),
      boost::make_iterator_range(b.begin(), b.end())
    ),
    boost::make_iterator_range(x.begin(), x.end())
  );

  std::generate(j_range.begin(), j_range.end(), gen);

  auto range = boost::combine(a, b);
  std::transform(range.begin(), range.end(),
                 c.begin(),
                 [](auto&& tuple) {
                  auto x = tuple.template get<0>();
                  auto y = tuple.template get<1>();
                  return std::fabs(x) + std::fabs(y) + 1;
                 });

  a[0] = 0;
  b[sz - 1] = 0;

  r[0] = c[0] * x[0] + b[0] * x[1];

  for (std::size_t i = 1; i < sz - 1; i++)
  {
    r[i] = a[i] * x[i - 1] + c[i] * x[i] + b[i] * x[i + 1];
  }

  r[sz - 1] = a[sz - 1] * x[sz - 2] + c[sz - 1] * x[sz - 1];
}

template <typename T>
void test_tma()
{
  std::size_t sz = MATRIX_SIZE;
  for (std::size_t i = 0; i < NUM_ITER; i++)
  {
    std::vector< T > a(sz);
    std::vector< T > c(sz);
    std::vector< T > b(sz);
    std::vector< T > r(sz);
    std::vector< T > x(sz);

    std::vector< T > result(sz);
    init_test_data(a, c, b, r, x);

    tma(a, c, b, r, result);

    double cond_num = cond(a, c, b);
    double eps =  std::numeric_limits< T >::epsilon();

    double norm1 = 0;
    double norm2 = 0;

    for (auto&& tuple : boost::combine(x, result))
    {
      T y1, y2;
      boost::tie(y1, y2) = tuple;

      double v1 = std::fabs(y1 - y2);
      double v2 = std::fabs(y1);

      norm1 = (v1 > norm1 ? v1 : norm1);
      norm2 = (v2 > norm2 ? v2 : norm2);
    }

    BOOST_REQUIRE_SMALL(norm1, cond_num * eps * norm2);
  }
}

#endif