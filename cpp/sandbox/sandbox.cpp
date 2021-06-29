#include <iostream>

#include <vector>

struct order_t {
  double close = 0.00;
};

class Foo {
public:
  order_t order;
  std::vector<order_t> orders;

  void append() { this->orders.push_back(this->order); }
  void setOrder(double close) { this->order = {.close = close}; }
};

double running_total() {
  double profits[] = {
      18.43, 5.40,   12.02,  7.14,   -5.72, 12.99, 13.93,   -4.55,
      35.91, -2.00,  -7.11,  -11.66, 16.23, 38.13, -142.60, 5.20,
      -2.22, -13.92, -16.29, -2.10,  1.92,  -9.61,
  };

  double sum = 0;

  for (double n : profits) {
    sum += n;
  }

  return sum;
}

int main() {
  Foo f;

  f.setOrder(4.44);
  f.append();
  f.setOrder(5.55);
  f.append();

  std::cout << f.orders.at(0).close << std::endl;
  std::cout << f.orders.at(1).close << std::endl;
}
