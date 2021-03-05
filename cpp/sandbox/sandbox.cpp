#include <iostream>
#include <math.h>

double sigmoid(const double x) { return 1 / (1 + exp(-x)); }
double t_sigmoid(const double x) { return 0.005 / (1 + exp(-(100 * x - 3))); }

int main() {
  const double tsla1 = (700.70 - 651.71) / 687.99;
  const double tsla2 = (668.00 - 603) / 652.00;
  const double amzn = (3058.13 - 2945.42) / 3012.00;

  std::cout << tsla1 << std::endl;
  std::cout << t_sigmoid(tsla1) << std::endl;
  std::cout << (t_sigmoid(tsla1) * 687.99) << std::endl << std::endl;

  std::cout << tsla2 << std::endl;
  std::cout << t_sigmoid(tsla2) << std::endl;
  std::cout << (t_sigmoid(tsla2) * 652.00) << std::endl << std::endl;

  std::cout << amzn << std::endl;
  std::cout << t_sigmoid(amzn) << std::endl;
  std::cout << (t_sigmoid(amzn) * 3012.00) << std::endl << std::endl;
}
