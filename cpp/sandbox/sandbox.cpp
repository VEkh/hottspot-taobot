#include <iostream>
#include <regex> // std::regex, std::regex_search

int main() {
  const char *symbol = "AMZN";

  bool should_stop_profit = std::regex_search(
      symbol, std::regex("sq|spot|amzn", std::regex_constants::icase));
  std::cout << should_stop_profit << std::endl;
}
