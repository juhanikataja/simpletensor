#include "tensor.h"


int main(int argc, char *argv[])
{
  tensor<double> a(2, 3, 3, 2);

  double some_data[4] = {1, 2, 3, 4};
  
  for (uint i = 0; i != a.getrank()-1; ++i)
    std::cout << a.getdims(i) << " ";

  std::cout << a.getdims(a.getrank()-1)<< std::endl;
  std::cout << a.getrank() << std::endl;

  a(1,2,2,1) = 1;

  std::cout << a(1,2,2,1) << std::endl;

  a.reset(some_data, 2,2);
  std::cout << a(1,1) <<std::endl;

  tensor<std::string> b(2,2);
  tensor<std::string> c;

  b(0,0) = "String";
  b(0,1) = "variables";
  b(1,0) = "work";
  b(1,1) = "too";

  c.reset(b.getdata(), 2,2);

  for (uint i = 0; i != c.getdims(0); ++i)
    for (uint j = 0; j != c.getdims(1); ++j)
      std::cout << c(i,j) << " ";

  std::cout << std::endl;

  return 0;
}
