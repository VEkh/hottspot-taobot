#include "lib/utils/float.cpp" // utils::float_
#include <iostream>            // std::cout

int main() {
  float f = 1.239182391;

  std::cout << utils::float_::to_currency(f) << std::endl;
}
