#include<iostream>
#include<vector>
#include<stdexcept>

typedef unsigned int uint;

template<typename M>
constexpr M product(M m)
{
  return m;
}

template<typename M1, typename ...M>
constexpr M1 product(M1 m1, M ...m)
{ 
  return m1 * product(m...); 
}

template<typename M>
constexpr M dimsum(M m)
{ 
  return 1; 
};

template<typename M1, typename ...M>
constexpr M1 dimsum(M1 m1, M ...m)
{ 
  return 1+dimsum(m...); 
};

uint partial_product(uint start, uint len, const uint b[])
{
  uint res = 1;
  for (size_t i = start; i != len ; ++i)
    res *= b[i];
  return res;
}

template<class T,uint... M>
class tensor
{
#ifdef RANGE_CHECK
#endif
public:
  tensor():rank(dimsum(M...)), dims {M...}
    {
      for (uint i = 0; i != dimsum(M...)-1; ++i)
        _point_multipliers[i] = partial_product(i+1,dimsum(M...),dims);
      _point_multipliers[rank-1] = 1;
    }
  ~tensor(){}
  const uint rank;
  const uint dims[dimsum(M...)];
  template<typename ...A> 
    T &operator() (A... a)
    {
#ifdef RANGE_CHECK
      if (sizeof...(a) != rank)
        throw std::runtime_error("wrong rank!\n");
#endif
      return data[point(a...)];
    }
  template<typename ...A> 
    const T &operator() (A... a) const
    {
#ifdef RANGE_CHECK
      if (sizeof...(a) != rank)
        throw std::runtime_error("wrong rank!\n");
#endif
      return data[point(a...)];
    }
private:

  T data[product(M...)];
  uint _point_multipliers[dimsum(M...)];

  template<typename ...A>
    uint point(A... a)
    {
#ifdef RANGE_CHECK
#endif
      const uint b[dimsum(M...)] = {a...};
      uint c = 0;
      for (uint i = 0; i != rank; ++i)
        c += b[i]*_point_multipliers[i];
      return c;
    }
};
