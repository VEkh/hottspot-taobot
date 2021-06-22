#include <cmath> // exp
#include <iostream>

double running_total() {
  double profits[] = {
      18.43, 5.40,  12.02,  7.14,  -5.72, 12.99,   13.93, -4.55, 35.91,
      -2.00, -7.11, -11.66, 16.23, 38.13, -142.60, 5.20,  -2.22,
  };

  double sum = 0;

  for (double n : profits) {
    sum += n;
  }

  return sum;
}

int main() { std::cout << running_total() << std::endl; }
