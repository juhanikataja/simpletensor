#include "multiarray.h"

using namespace std;

int main(int argc, char *argv[])
{
  double b;
  for (uint m = 1; m != M_MAX; ++m)
  for (uint n = 1; n != N_MAX; ++n)
    {
      static_mat<double,2,2> a;
      a(0,0) = 1/n;
      b += a(0,0);
    }
  cout << b<< std::endl;
  return 0;
}
