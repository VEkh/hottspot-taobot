#include <cmath> // exp
#include <iostream>

double fn(const double buy_sell_ratio) {
  const double x = buy_sell_ratio;
  const double x_multiplier = 10;
  const double x_shift = -1.25;
  const double y_multiplier = 0.2;
  const double y_shift = 0.15;

  const double y =
      (y_multiplier / (1 + exp(-(x_multiplier * (x + x_shift))))) + y_shift;

  return y;
}

int main() { std::cout << fn(1.7) << std::endl; }
