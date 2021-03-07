#include <iostream>
#include <math.h>

double sigmoid(const double day_range, const double reference_price) {
  const double x = day_range / reference_price;
  const double x_scale = 100.0;
  const double y_scale = 200.0;
  const double y_shift = 3;

  const double y = (y_scale / (1 + exp(x_scale * x))) + y_shift;

  return y;
}

int main() {
  // std::cout << ((20) / 687.99) << std::endl;
  // std::cout << (2.0 / (20)) << std::endl << std::endl;

  std::cout << (0.04 * 687.99) << std::endl;
  // std::cout << (2.00 / (700.70 - 651.71)) << std::endl << std::endl;

  // std::cout << ((627.84 - 539.49) / 626.06) << std::endl;
  // std::cout << (2 / (627.84 - 539.49)) << std::endl << std::endl;

  std::cout << ((123.60 - 118.62) / 121.75) << std::endl << std::endl;

  std::cout << "2%: " << sigmoid(2, 100) << std::endl << std::endl;
  std::cout << "4%: " << sigmoid(4, 100) << std::endl << std::endl;
  std::cout << "5%: " << sigmoid(5, 100) << std::endl << std::endl;
  std::cout << "7%: " << sigmoid(7, 100) << std::endl << std::endl;
  std::cout << "14%: " << sigmoid(14, 100) << std::endl << std::endl;
}
