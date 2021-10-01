#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf

#include "deps.cpp"
#include <string>

struct fu {
  int foo = 1;
};

int main() {
  fu f;

  f.foo = 2;

  printf("%i\n", f.foo);

  f = fu();

  printf("%i\n", f.foo);
}
