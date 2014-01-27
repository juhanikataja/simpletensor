#include "tensor.h"

double sum(tensor<double, 2, 3, 3, 2> a)
{
  return 1;
}

int main(int argc, char *argv[])
{
  tensor<double, 2, 3, 3, 2> a;
  for (uint i = 0; i != a.rank-1; ++i)
    std::cout << a.dims[i] << " ";
  std::cout << a.dims[a.rank-1] << std::endl;
  std::cout << a.rank << std::endl;
  a(1,2,2,1) = 1;
  std::cout << a(1,2,2,1) << std::endl;

  tensor<std::string, 2, 2> b;
  b(0,0) = "moi";
  std::cout << b(0,0) << std::endl;
  return (int)sum(a);
}
