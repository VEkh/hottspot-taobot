#include "lib/utils/string.cpp"
#include <iostream>

struct structure {
  int foo = 1;
  int bar;
};

int main() {
  structure yerr = {.foo = 2, .bar = 100};

  std::cout << "foo: " << yerr.foo << std::endl;
  std::cout << "bar: " << yerr.bar << std::endl;
}
