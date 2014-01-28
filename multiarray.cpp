#include "multiarray.h"

using namespace std;

int main(int argc, char *argv[])
{
  multiarray<double, 2, 2> b;
  for (uint m = 0; m != 2; ++m)
    for (uint n = 0; n != 2; ++n)
      b[m][n] = 0;
  for (uint m = 1; m != M_MAX; ++m)
    for (uint n = 1; n != N_MAX; ++n)
      {
        multiarray<double, 2,2> a;
        a[0][0] = 1/(double)n;
        a[1][0] += a[0][0];
        b[0][0] += a[0][0];
      }
  cout << b[0][0] << std::endl;
  return 0;
}
