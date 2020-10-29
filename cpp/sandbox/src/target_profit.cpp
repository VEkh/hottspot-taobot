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

void log_symbol(std::string symbol) {
  std::cout << "\n=========================\n" << std::endl;
  std::cout << symbol << std::endl;

  for (int i = 0; i < symbol.size(); i++) {
    std::cout << "-";
  }

  std::cout << std::endl;
}

int main() {
  std::string loss_close_price_string;
  std::string loss_open_price_string;
  std::string win_order_type;
  std::string symbol;
  std::string win_open_price_string;

  std::cout << "Symbol: ";
  std::cin >> symbol;

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

  float adjusted_stop_loss;
  float adjusted_stop_loss_limit;
  float cancel_stop_loss_price;
  float limit_price;
  float target_gain = 1.2 * loss;

  if (win_order_type == "BUY") {
    adjusted_stop_loss = win_open_price + (0.2 * 0.9 * target_gain);
    adjusted_stop_loss_limit = win_open_price + (0.2 * target_gain);
    cancel_stop_loss_price = win_open_price + (0.9 * target_gain);
    limit_price = win_open_price + target_gain;
  } else if (win_order_type == "SELL_SHORT") {
    adjusted_stop_loss = win_open_price - (0.2 * 0.9 * target_gain);
    adjusted_stop_loss_limit = win_open_price - (0.2 * target_gain);
    cancel_stop_loss_price = win_open_price - (0.9 * target_gain);
    limit_price = win_open_price - target_gain;
  }

  log_symbol(symbol);

  std::cout << "TARGET GAIN:         " << utils::float_::toCurrency(target_gain)
            << std::endl;

  std::cout << "ADJUSTED STOP LOSS:  Stop Limit: "
            << utils::float_::toCurrency(adjusted_stop_loss_limit)
            << " • Stop: " << utils::float_::toCurrency(adjusted_stop_loss)
            << std::endl;

  std::cout << "CANCEL STOP LOSS AT: "
            << utils::float_::toCurrency(cancel_stop_loss_price) << std::endl;

  std::cout << "LIMIT PRICE:         " << utils::float_::toCurrency(limit_price)
            << std::endl;
}
