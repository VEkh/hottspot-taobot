#include <cmath>    // std::abs
#include <iomanip>  // std::setprecision
#include <iostream> // std::cout, std::endl, std::fixed
#include <sstream>  // std::stringstream
#include <string> // std::stof, std::string, std::string::erase, std::string::find

std::string stripCommas(std::string input) {
  int position = input.find(",");

  while (position != -1) {
    input.erase(position, 1);
    position = input.find(",");
  }

  return input;
}

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

  // Old percentage:  0.12954141515764692
  // float target_stop_to_open = ((high - low) * 0.15) / current_price;
  // float target_stop_to_close = ((high - low) * 0.7) / current_price;

  // std::cout << "\n***OPEN***" << std::endl;

  // std::cout << "Trailing stop %: " <<
  // toRoundedPercentage(target_stop_to_open)
  //           << std::endl;

  // std::cout << "BUY target price: "
  //           << toCurrency(current_price * (1 + target_stop_to_open))
  //           << std::endl;

  // std::cout << "SHORT SELL target price: "
  //           << toCurrency(current_price * (1 - target_stop_to_open))
  //           << std::endl;

  // std::cout << "\n\n***CLOSE***" << std::endl;

  // std::cout << "Trailing stop %: " <<
  // toRoundedPercentage(target_stop_to_close)
  //           << std::endl;

  // 1. Wait for threshold movement
  // 2. Look for the right kind of momentum before closing the losing side
  // 3. Close losing side.
  // 4. Wait until winning side reaches 1.25 x the threshold percentage movement
  // (??)
  //    * Be more decisive about the exit and what to do if it isn't raeched
  //    * Maybe re-create a trailing stop when the price reaches the target
  float loser_trailing_stop = ((high - low) * 0.25) / current_price;
  float target_movement = 1.15 * loser_trailing_stop;

  std::cout << "\n=======================\n" << std::endl;

  std::cout << "Trailing Stop %: " << toRoundedPercentage(loser_trailing_stop)
            << std::endl;

  std::cout << "Target Movement %: " << toRoundedPercentage(target_movement)
            << std::endl;
}
