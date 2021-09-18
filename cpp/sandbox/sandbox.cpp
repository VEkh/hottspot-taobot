#include <stdio.h> // printf

template <typename T> bool is_even(T n) {
  T addend = 1;

  return (n + addend) % 2 == 0;
}

int main() { printf("%i\n", is_even(1)); }
