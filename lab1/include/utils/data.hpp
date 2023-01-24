#ifndef DATA_HPP
#define DATA_HPP

template< typename T = double >
using func_t = T (*)(T);

template <typename T = double>
struct Data
{
  const T R_L;
  const T R_R;
  const func_t< T > u;
  const func_t< T > k;
  const func_t< T > q;
  const func_t< T > f;
  const T nu_1;
  const T nu_2;
};

#endif