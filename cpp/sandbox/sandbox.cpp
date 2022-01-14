#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include <algorithm> // std::min
#include <string>

int main() {
  std::string str = "1.273749";

  printf("%i\n", std::stoi(str));
}
