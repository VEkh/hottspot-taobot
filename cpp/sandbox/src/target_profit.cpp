#include "utils/float.cpp" // utils::float_::toCurrency
#include <cmath>           // std::abs
#include <iostream>        // std::cout, std::endl, std::fixed
#include <string>          // std::stof, std::string

std::string stripCommas(std::string input) {
  int position = input.find(",");

  while (position != -1) {
    input.erase(position, 1);
    position = input.find(",");
  }

  return input;
}

int main() {
  int quantity;
  std::string loss_close_price_string;
  std::string loss_open_price_string;
  std::string win_order_type;
  std::string symbol;
  std::string win_open_price_string;

  std::cout << "Symbol: ";
  std::cin >> symbol;

  std::cout << "Quantity: ";
  std::cin >> quantity;

  std::cout << "Win Order Type (BUY | SELL_SHORT): ";
  std::cin >> win_order_type;

  std::cout << "Win Open Price: ";
  std::cin >> win_open_price_string;

  std::cout << "Loss Open: ";
  std::cin >> loss_open_price_string;

  std::cout << "Loss Close: ";
  std::cin >> loss_close_price_string;

  float loss = std::abs(std::stof(stripCommas(loss_open_price_string)) -
                        std::stof(stripCommas(loss_close_price_string)));

  float win_open_price = std::stof(stripCommas(win_open_price_string));

  float target_gain = 1.3 * loss * quantity;
  float win_target_price;

  if (win_order_type == "BUY") {
    win_target_price = win_open_price + (target_gain / quantity);
  } else if (win_order_type == "SELL_SHORT") {
    win_target_price = win_open_price - (target_gain / quantity);
  }

  std::cout << "\n=======================\n" << std::endl;

  std::cout << symbol
            << " target gain amount: " << utils::float_::toCurrency(target_gain)
            << std::endl;
  std::cout << symbol
            << " target price: " << utils::float_::toCurrency(win_target_price)
            << std::endl;
}
