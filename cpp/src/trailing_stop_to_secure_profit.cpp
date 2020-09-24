#include <iomanip>  // std::setprecision
#include <iostream> // std::cout, std::endl
#include <sstream>  // std::stringstream
#include <string>   // std::string

std::string toRoundedPercentage(float val) {
  std::stringstream result;

  result << std::setprecision(4) << std::fixed << (val * 100.0);
  return result.str();
}

int main(int argc, char *argv[]) {
  float current_price;
  float price_paid;
  int quantity;
  float target_exit_price;
  float target_percent_gain;
  float target_stop;
  std::string open_order_type;

  std::cout << "Open Order Type (BUY | SELL_SHORT): ";
  std::cin >> open_order_type;

  std::cout << "Current Price: ";
  std::cin >> current_price;

  std::cout << "Price Paid: ";
  std::cin >> price_paid;

  std::cout << "Quantity: ";
  std::cin >> quantity;

  std::cout << "Target Percent Gain: ";
  std::cin >> target_percent_gain;

  target_percent_gain = target_percent_gain / 100.0;

  if (open_order_type == "BUY") {
    target_exit_price = (1 + target_percent_gain) * price_paid;
    target_stop = (current_price - target_exit_price) / current_price;
  } else if (open_order_type == "SELL_SHORT") {
    target_exit_price = (1 - target_percent_gain) * price_paid;
    target_stop = (target_exit_price - current_price) / current_price;
  }

  std::cout << "\n\nTarget exit price: $" << target_exit_price << " (x"
            << quantity << " = $" << (quantity * target_exit_price) << ")"
            << std::endl;

  std::cout << "(Approximate) Target trailing stop percentage is: "
            << toRoundedPercentage(target_stop) << std::endl;
}
