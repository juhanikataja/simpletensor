#include "tensor.h"

double sum(tensor<double, 2, 3, 3, 2> a)
{
  return 1;
}

double sum(dyn_tensor<double> a)
{
  return 1;
}

int main(int argc, char *argv[])
{
  dyn_tensor<double> a(2, 3, 3, 2);
  
  for (uint i = 0; i != a.getrank()-1; ++i)
    std::cout << a.getdims(i) << " ";

  std::cout << a.getdims(a.getrank()-1)<< std::endl;
  std::cout << a.getrank() << std::endl;
  a(1,2,2,1) = 1;
  std::cout << a(1,2,2,1) << std::endl;

  dyn_tensor<std::string> b(2,2);
  b(0,0) = "moi";
  std::cout << b(0,0) << std::endl;
  return (int)sum(a);
}
