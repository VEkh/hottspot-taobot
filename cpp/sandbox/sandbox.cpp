#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf

#include <iomanip>  // std::setw
#include <iostream> // std::fixed
#include <sstream>  // std::ostringstream
#include <string>

int main() {
  std::ostringstream out;

  out << std::setfill('0') << std::setw(2) << 1 << ":" << std::setfill('0')
      << std::setw(2) << 1;

  printf("%s\n", out.str().c_str());
}
