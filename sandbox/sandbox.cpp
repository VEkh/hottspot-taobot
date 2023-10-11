#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include <map> // std::map

class Foo {
public:
  static int mult(const int);
};

int Foo::mult(const int n) { return n * 2; }

int main(int argc, char *argv[]) {
  std::map<int, int> nums = {{1, 1}};

  std::map<int, int>::reverse_iterator it = nums.rbegin();

  printf("%i: %i\n", it->first, it->second);
  printf("%i\n", Foo::mult(2));
}
