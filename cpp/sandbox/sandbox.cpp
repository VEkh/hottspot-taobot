#include <locale.h> // setlocale
#include <stdio.h>  // printf
#include <vector>   // std::vector

double running_total(const std::vector<double> &returns) {
  double sum = 0;

  for (double n : returns) {
    sum += n;
  }

  return sum;
}

int main() {
  std::vector<double> all_returns = {
      18.43,   5.40,   12.02,    7.14,    -5.72,   12.99,   13.93,   -4.55,
      35.91,   -2.00,  -7.11,    -11.66,  16.23,   38.13,   -142.60, 5.20,
      -2.22,   -13.92, -16.29,   -2.10,   1.92,    -9.61,   -10.25,  -2.62,
      5.27,    32.46,  59.86,    167.31,  -50.05,  -202.92, 155.66,  173.43,
      247.97,  264.09, -1505.21, -598.76, -157.98, 10.51,   -39.94,  -166.16,
      101.66,  160.27, 130.38,   340.12,  243.36,  240.00,  68.00,   -469.07,
      -419.72, 37.63,  44.74,    241.73,  338.38,  311.50,  198.92,  -622.55,
      -473.15, 140.64, -261.35,  123.96,  122.76,
  };

  std::vector<double> weeks_returns = {
      140.64,
      -261.35,
      123.96,
      122.76,
  };

  setlocale(LC_NUMERIC, "");
  printf("* Week's Return: %+'.2f\n", running_total(weeks_returns));
  printf("* Total Return: %+'.2f\n", running_total(all_returns));
}
