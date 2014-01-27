#include<iostream>
#include<vector>
#include<stdexcept>
#include<tuple>
#include<array>
#include<complex>

#define M_MAX 2000
#define N_MAX 1000000

#define REAL double
#define COMPLEX std::complex<double>
#define UINT size_t

typedef unsigned int uint;

template<typename T, uint... dims> struct multiarray;

template<typename T, uint dim, uint... dims>
struct multiarray<T, dim, dims...>
{
    //std::array<multiarray<T,dims...>,dim> data;
    multiarray<T,dims...> data[dim];
    multiarray<T,dims...> &operator[](uint n){return data[n];};
};

template<typename T, uint dim>
struct multiarray<T,dim>
{
   //std::array<T,dim> data;
   T data[dim];
   T &operator[](uint n){return data[n];};
};

/*
 *template<typename T>
 *class multiarray<T>{
 *};
 */

template <typename T, UINT M, UINT N>
class static_mat
{
public: 
  static_mat(){}
  inline UINT get_M() const {return M;}
  inline UINT get_N() const {return N;}
  inline T &operator()(const UINT m, const UINT n)
  {
    return ae[m * N + n];
  }
  
  inline const T &operator()(const UINT m, const UINT n) const
  {
    return ae[m * N + n];
  }
  inline T *get() {return ae;}
  inline const T *get() const {return ae;}
  inline void operator=(const T alkio) 
  {
    for (UINT m = 0; m != M * N; ++m)
      ae[m] = alkio;
  }
  inline void operator*=(const T alkio)
  {
    for (UINT m = 0; m != M * N; ++m)
      ae[m] *= alkio;
  }
  template<typename U> inline void operator*=(const U alkio)
  {
    for (UINT m = 0; m != M * N; ++m)
      ae[m] *= alkio;
  }
  inline void operator+=(const T alkio)
  {
    for (UINT m = 0; m != M * N; ++m)
      ae[m] += alkio;
  }
  template<typename U> inline void operator+=(const U alkio)
  {
    for (UINT m = 0; m != M * N; ++m)
      ae[m] += alkio;
  }
  inline void operator-=(const T alkio)
  {
    for (UINT m = 0; m != M * N; ++m)
      ae[m] -= alkio;
  }
  template<typename U> inline void operator-=(const U alkio)
  {
    for (UINT m = 0; m != M * N; ++m)
      ae[m] -= alkio;
  }
  inline void operator/=(const T alkio)
  {
    const T invalkio = 1.0 / alkio;
    for (UINT m = 0; m != M * N; ++m)
      ae[m] *= invalkio;
  }
  template<typename U> inline void operator/=(const U alkio)
  {
    const U invalkio = 1.0 / alkio;
    for (UINT m = 0; m != M * N; ++m)
      ae[m] *= invalkio;
  }
private:
  T ae[M * N];
};
