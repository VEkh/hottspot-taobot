#include <cstdio> // printf

double running_total() {
  double profits[] = {
      18.43, 5.40,   12.02,  7.14,   -5.72,  12.99,   13.93,   -4.55,
      35.91, -2.00,  -7.11,  -11.66, 16.23,  38.13,   -142.60, 5.20,
      -2.22, -13.92, -16.29, -2.10,  1.92,   -9.61,   -10.25,  -2.62,
      5.27,  32.46,  59.86,  167.31, -50.05, -202.92, 155.66,  173.43,
  };

  double sum = 0;

  for (double n : profits) {
    sum += n;
  }

  return sum;
}

int main() { printf("Running Total: %.2f\n", running_total()); }
