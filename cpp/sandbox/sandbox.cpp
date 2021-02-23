#include <cstring>
#include <iostream>

int main() {
  int n = 123;
  int *ptr;

  ptr = &n;
  *ptr = 444;

  if (ptr) {
    std::cout << n << std::endl;
    std::cout << *ptr << std::endl;
  }
}
