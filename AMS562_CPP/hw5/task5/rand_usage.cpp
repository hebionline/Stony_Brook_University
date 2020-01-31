// compile with:
//      g++ -std=c++11 rand_usage.cpp
// run:
//      ./a.out

#include <iostream>
#include "rand.hpp"

int main() {
  ams562::RandGen gen;
  std::cout << gen.generate() << '\n';
  return 0;
}
