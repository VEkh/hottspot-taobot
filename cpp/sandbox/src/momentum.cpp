#include "utils/float.cpp"  // utils::float::toCurrency
#include "utils/string.cpp" // utils::string::stripCommas
#include <ctime>            // std::localtime, std::time, std::time_t, std::tm
#include <iostream>         // std::cout, std::endl, std::fixed
#include <string> // std::stof, std::string, std::string::erase, std::string::find

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
  std::string high_input;
  std::string low_input;
  std::string symbol;

  std::cout << "Symbol: ";
  std::cin >> symbol;

  std::cout << "Current: ";
  std::cin >> current_price_input;

  std::cout << "Low: ";
  std::cin >> low_input;

  std::cout << "High: ";
  std::cin >> high_input;

  float current_price =
      std::stof(utils::string::stripCommas(current_price_input));
  float high = std::stof(utils::string::stripCommas(high_input));
  float low = std::stof(utils::string::stripCommas(low_input));
  float range_movement = 0.125;

  std::time_t t = std::time(0);
  std::tm *now = std::localtime(&t);
  bool is_market_open = (now->tm_hour - 5) < 10;

  if (is_market_open) {
    range_movement *= 2;
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
  float buy_close_stop = current_price + (0.2 * open_stop_price_change);
  float buy_close_stop_limit =
      current_price + (0.9 * 0.2 * open_stop_price_change);

  // Sell Short
  float sell_short_open_stop = current_price - open_stop_price_change;
  float sell_short_open_stop_limit =
      current_price - open_stop_limit_price_change;
  float sell_short_close_limit =
      current_price - (target_profit_ratio * open_stop_limit_price_change);
  float sell_short_close_stop = current_price - (0.2 * open_stop_price_change);
  float sell_short_close_stop_limit =
      current_price - (0.9 * 0.2 * open_stop_price_change);

  log_symbol(symbol);
  log_target_movement_percentage(target_movement, is_market_open);

  std::cout << "\n=========================\n" << std::endl;

  std::cout << "BUY (OPEN)                  => Stop Limit: "
            << utils::float_::toCurrency(buy_open_stop_limit)
            << " • Stop: " << utils::float_::toCurrency(buy_open_stop)
            << std::endl;

  std::cout << "BUY (CLOSE)                 => Stop Limit: "
            << utils::float_::toCurrency(buy_close_stop_limit)
            << " • Stop: " << utils::float_::toCurrency(buy_close_stop)
            << std::endl;

  std::cout << "BUY (CLOSE) (PROFIT)        =>      Limit: "
            << utils::float_::toCurrency(buy_close_limit) << std::endl;

  std::cout << "\n=========================\n" << std::endl;

  std::cout << "SELL SHORT (OPEN)           => Stop Limit: "
            << utils::float_::toCurrency(sell_short_open_stop_limit)
            << " • Stop: " << utils::float_::toCurrency(sell_short_open_stop)
            << std::endl;

  std::cout << "SELL SHORT (CLOSE)          => Stop Limit: "
            << utils::float_::toCurrency(sell_short_close_stop_limit)
            << " • Stop: " << utils::float_::toCurrency(sell_short_close_stop)
            << std::endl;

  std::cout << "SELL SHORT (CLOSE) (PROFIT) =>      Limit: "
            << utils::float_::toCurrency(sell_short_close_limit) << std::endl;
}
