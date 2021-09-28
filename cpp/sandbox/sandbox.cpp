#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf

#include "deps.cpp"
#include <string>

int main() {
  std::string i = "12484";

  printf("%i\n", (int)std::stod(i));
}
