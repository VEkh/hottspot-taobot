#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include <string> // std::stoi

int main() {
  const std::string str = "";

  printf("Num: %i\n", std::stoi(str));
}
