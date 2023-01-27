#define BOOST_TEST_MODULE TMA_TEST
#include <boost/test/unit_test.hpp>

#include "test_utils.hpp"

BOOST_AUTO_TEST_CASE( tma_float )
{
  test_tma< float >();
}

BOOST_AUTO_TEST_CASE( tma_double )
{
  test_tma< double >();
}