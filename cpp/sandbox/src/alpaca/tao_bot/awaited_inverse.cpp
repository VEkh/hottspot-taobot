#ifndef ALPACA__TAO_BOT_awaited_inverse
#define ALPACA__TAO_BOT_awaited_inverse

#include "read_sibling_performance.cpp" // read_sibling_performance
#include "should_open_position.cpp"     // should_open_position
#include "tao_bot.h"                    // Alpaca::TaoBot, fmt, performance_t
#include <iostream>                     // std::cout, std::endl
#include <map>                          // std::map
#include <stdio.h>                      // printf
#include <string>                       // std::string
#include <unistd.h>                     // usleep

bool Alpaca::TaoBot::awaited_inverse() {
  if (!should_open_position()) {
    return false;
  }

  std::map<std::string, std::string> inverse_symbols = {
      {"SQQQ", "TQQQ"},
      {"TQQQ", "SQQQ"},
  };

  const std::string inverse_symbol = inverse_symbols[std::string(this->symbol)];

  if (inverse_symbol.empty()) {
    return false;
  }

  json inverse_performance = read_sibling_performance(inverse_symbol);

  if (!inverse_performance.contains("positions")) {
    return false;
  }

  const bool out =
      inverse_performance["positions"].size() != this->closed_positions.size();

  if (out) {
    std::cout << fmt.bold << fmt.yellow << std::endl;
    std::cout << "Awaiting inverse " << fmt.blue;
    std::cout << "<" << inverse_symbol << "> " << fmt.yellow;
    printf("to close\n");
    std::cout << fmt.reset;

    usleep(1e6);
  }

  return out;
}

#endif
