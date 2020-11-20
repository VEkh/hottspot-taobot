#include "utils/float.cpp"  // utils::float::toCurrency
#include "utils/string.cpp" // utils::string::split, utils::string::stripCommas
#include <ctime>            // std::localtime, std::time, std::time_t, std::tm
#include <iostream>         // std::cout, std::endl, std::fixed
#include <string> // std::string::erase, std::string::find, std::getline, std::stof, std::string,
#include <vector> // std::vector

void log_target_movement_percentage(float target_movement,
                                    bool is_market_open) {
  std::cout << "Stop %";

  if (is_market_open) {
    std::cout << " (At Market Open)";
  }

  std::cout << ": " << utils::float_::toRoundedPercentage(target_movement)
            << std::endl;
}

void log_symbol(std::string symbol) {
  std::cout << "\n=========================\n" << std::endl;
  std::cout << symbol << std::endl;

  for (int i = 0; i < symbol.size(); i++) {
    std::cout << "-";
  }

  std::cout << "\n" << std::endl;
}

int main() {
  std::string current_price_input;
  std::string day_range_input;
  std::string symbol;

  std::cout << "Symbol: ";
  std::getline(std::cin, symbol);

  std::cout << "Current: ";
  std::getline(std::cin, current_price_input);

  std::cout << "Day Range: ";
  std::getline(std::cin, day_range_input);

  std::vector<std::string> day_range =
      utils::string::split(day_range_input, "-");

  float current_price =
      std::stof(utils::string::stripCommas(current_price_input));
  float high = std::stof(utils::string::stripCommas(day_range[1]));
  float low = std::stof(utils::string::stripCommas(day_range[0]));
  float range_movement = 0.15;

  std::time_t t = std::time(0);
  std::tm *now = std::localtime(&t);
  bool is_market_open = (now->tm_hour - 6) < 10;

  if (is_market_open) {
    range_movement *= 1.5;
  }

  float target_movement = ((high - low) * range_movement) / current_price;
  float target_profit_ratio = 1.2;
  float open_stop_price_change = 0.9 * (target_movement * current_price);
  float open_stop_limit_price_change = target_movement * current_price;

  // Buy
  float buy_open_stop = current_price + open_stop_price_change;
  float buy_open_stop_limit = current_price + open_stop_limit_price_change;
  float buy_close_limit =
      current_price + (target_profit_ratio * open_stop_limit_price_change);

  // Sell Short
  float sell_short_open_stop = current_price - open_stop_price_change;
  float sell_short_open_stop_limit =
      current_price - open_stop_limit_price_change;
  float sell_short_close_limit =
      current_price - (target_profit_ratio * open_stop_limit_price_change);

  log_symbol(symbol);
  log_target_movement_percentage(target_movement, is_market_open);

  std::cout << "\n=========================\n" << std::endl;

  std::cout << "BUY (OPEN)                  => Stop Limit: "
            << utils::float_::toCurrency(buy_open_stop_limit)
            << " • Stop: " << utils::float_::toCurrency(buy_open_stop)
            << std::endl;

  std::cout << "BUY (CLOSE) (PROFIT)        =>      Limit: "
            << utils::float_::toCurrency(buy_close_limit) << std::endl;

  std::cout << "\n=========================\n" << std::endl;

  std::cout << "SELL SHORT (OPEN)           => Stop Limit: "
            << utils::float_::toCurrency(sell_short_open_stop_limit)
            << " • Stop: " << utils::float_::toCurrency(sell_short_open_stop)
            << std::endl;

  std::cout << "SELL SHORT (CLOSE) (PROFIT) =>      Limit: "
            << utils::float_::toCurrency(sell_short_close_limit) << std::endl;
}
