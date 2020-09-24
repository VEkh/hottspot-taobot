#include <cmath>    // std::abs
#include <iomanip>  // std::setprecision
#include <iostream> // std::cout, std::endl, std::fixed
#include <sstream>  // std::stringstream

std::string toCurrency(float val) {
  std::stringstream result;

  result << std::setprecision(2) << std::fixed << val;
  return result.str();
}

std::string toRoundedPercentage(float val) {
  std::stringstream result;

  result << std::setprecision(4) << std::fixed << (val * 100.0);
  return result.str();
}

int main() {
  float current_price;
  float high;
  float low;
  std::string symbol;

  std::cout << "Symbol: ";
  std::cin >> symbol;

  std::cout << "Current Price: ";
  std::cin >> current_price;

  std::cout << "Low: ";
  std::cin >> low;

  std::cout << "High: ";
  std::cin >> high;

  // Old percentage:  0.12954141515764692
  float target_stop_to_open = ((high - low) * 0.2) / current_price;
  float target_stop_to_close = ((high - low) * 0.7) / current_price;

  std::cout << "\n***OPEN***" << std::endl;

  std::cout << "Trailing stop %: " << toRoundedPercentage(target_stop_to_open)
            << std::endl;

  std::cout << "BUY target price: "
            << toCurrency(current_price * (1 + target_stop_to_open))
            << std::endl;

  std::cout << "SHORT SELL target price: "
            << toCurrency(current_price * (1 - target_stop_to_open))
            << std::endl;

  std::cout << "\n\n***CLOSE***" << std::endl;

  std::cout << "Trailing stop %: " << toRoundedPercentage(target_stop_to_close)
            << std::endl;
}
