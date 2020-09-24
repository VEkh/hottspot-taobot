#include <iomanip>
#include <iostream>
#include <sstream>

int main() {
  double val = 3.14159;
  std::stringstream tmp;
  tmp << std::setprecision(4) << std::fixed << val;

  std::cout << tmp.str() << std::endl;
  double new_val = std::stod(tmp.str()); // new_val = 3.143

  std::cout << new_val << std::endl;
}
