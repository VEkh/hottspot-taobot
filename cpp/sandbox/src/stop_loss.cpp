#include "utils/float.cpp" // utils::float::toCurrency
#include <ctime>           // std::localtime, std::time, std::time_t, std::tm
#include <iostream>        // std::cout, std::endl, std::fixed
#include <string> // std::stof, std::string, std::string::erase, std::string::find

std::string stripCommas(std::string input) {
  int position = input.find(",");

  while (position != -1) {
    input.erase(position, 1);
    position = input.find(",");
  }

  return input;
}

void log_stop_loss_percentage(float stop_loss, bool is_market_open) {
  std::cout << "Stop %";

  if (is_market_open) {
    std::cout << " (At Market Open)";
  }

  std::cout << ": " << utils::float_::toRoundedPercentage(stop_loss)
            << std::endl;
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
  std::string price_executed_input;
  std::string high_input;
  std::string low_input;
  std::string symbol;

  std::cout << "Symbol: ";
  std::cin >> symbol;

  std::cout << "Low: ";
  std::cin >> low_input;

  std::cout << "High: ";
  std::cin >> high_input;

  std::cout << "Price Executed of Loser: ";
  std::cin >> price_executed_input;

  float price_executed = std::stof(stripCommas(price_executed_input));
  float high = std::stof(stripCommas(high_input));
  float low = std::stof(stripCommas(low_input));
  float range_movement = 0.125;

  std::time_t t = std::time(0);
  std::tm *now = std::localtime(&t);
  bool is_market_open = (now->tm_hour - 5) < 10;

  log_symbol(symbol);

  if (is_market_open) {
    range_movement *= 2;
  }

  float stop_loss = ((high - low) * range_movement) / price_executed;
  float stop = 0.9 * (stop_loss * price_executed);
  float stop_limit = stop_loss * price_executed;

  float sell_stop = price_executed - stop;
  float sell_stop_limit = price_executed - stop_limit;

  float buy_to_cover_stop = price_executed + stop;
  float buy_to_cover_stop_limit = price_executed + stop_limit;

  log_stop_loss_percentage(stop_loss, is_market_open);

  std::cout << "BUY TO COVER => Stop Limit: "
            << utils::float_::toCurrency(buy_to_cover_stop_limit)
            << " • Stop: " << utils::float_::toCurrency(buy_to_cover_stop)
            << std::endl;

  std::cout << "SELL         => Stop Limit: "
            << utils::float_::toCurrency(sell_stop_limit)
            << " • Stop: " << utils::float_::toCurrency(sell_stop) << std::endl;
}
