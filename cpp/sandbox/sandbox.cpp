#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include <fstream> // std::ifstream
#include <string>  //std::getline, std::string

struct obj {
  int n = 0;
};

obj create_obj(int val) {
  obj o_ = {.n = val};
  return o_;
};

int main() {
  obj o = create_obj(5);

  printf("o val: %i\n", o.n);
}
