#include <iostream> // std::cout
#include <stdlib.h> // strtol
#include <string>   // stoi

int main() {
  int i = strtol("1", nullptr, 10);
  std::cout << i << std::endl;
}
