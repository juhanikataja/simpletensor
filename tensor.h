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

template<typename A>
 void print_pack(A a)
{
  std::cout << a << std::endl;
}

template<typename A, typename ...B>
 void print_pack(A a, B... b)
{
  std::cout << a << std::endl;
  print_pack(b...);
}

uint partial_product(uint start, uint len, const uint b[])
{
  uint res = 1;
  for (size_t i = start; i != len ; ++i)
    res *= b[i];
  return res;
}

template <typename A, typename... B>
A rest_prod(A a, B... b)
{
  return product(b...);
}


#define RANGE_CHECK
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

  constexpr uint get_pointer(uint m)
    { return 0; }

  template<typename A0, typename ...A>
  constexpr uint get_pointer(uint m, A0 a0, A... a)
    { return _point_multipliers[m]*a0 + get_pointer(m+1,a...); }

#ifdef RANGE_CHECK
  void range_check(uint m) {};
  template<typename A0, typename... A>
    void range_check(uint m, A0 a0, A... a)
      {
        if ((dims[m] <= a0) || (a0 < 0))
          throw std::runtime_error("range_check failed\n");
        else
          range_check(m+1, a...);
      }
#endif

  template<typename ...A>
    uint point(A... a)
    {
#ifdef RANGE_CHECK
      range_check(0,a...);
#endif
      const uint c = get_pointer(0,a...);
      return c;
    }
};

