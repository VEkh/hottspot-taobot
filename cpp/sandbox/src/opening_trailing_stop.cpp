#include "utils/float.cpp" // utils::float::toCurrency
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

int main() {
  std::string current_price_input;
  std::string high_input;
  std::string low_input;
  std::string symbol;

  std::cout << "Symbol: ";
  std::cin >> symbol;

  std::cout << "Current Price: ";
  std::cin >> current_price_input;

  std::cout << "Low: ";
  std::cin >> low_input;

  std::cout << "High: ";
  std::cin >> high_input;

  float current_price = std::stof(stripCommas(current_price_input));
  float high = std::stof(stripCommas(high_input));
  float low = std::stof(stripCommas(low_input));

  float loser_trailing_stop = ((high - low) * 0.125) / current_price;
  float lower_limit = current_price - (loser_trailing_stop * current_price);
  float upper_limit = current_price + (loser_trailing_stop * current_price);

  std::cout << "\n=======================\n" << std::endl;

  std::cout << symbol << " trailing Stop %: "
            << utils::float_::toRoundedPercentage(loser_trailing_stop)
            << std::endl;

  std::cout << symbol
            << " BUY TO COVER limit: " << utils::float_::toCurrency(upper_limit)
            << std::endl;

  std::cout << symbol
            << " SELL limit: " << utils::float_::toCurrency(lower_limit)
            << std::endl;
}
