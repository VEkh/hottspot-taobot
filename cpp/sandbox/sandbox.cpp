#include <iostream>
#include <math.h> // exp

double sigmoid(const double x) {
  const double max_period = 5 * 60;
  const double min_period = 1 * 60;
  const double x_scale = -15;
  const double x_shift = -0.2;
  const double y_shift = min_period;
  const double y_scale = max_period - min_period;
  const double y = (y_scale / (1 + exp(x_scale * (x + x_shift)))) + y_shift;

  return y;
}

int main() { std::cout << (25.0 / 89) << std::endl; }
