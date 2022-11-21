#ifndef ALPACA__TAO_BOT_is_first_position_long
#define ALPACA__TAO_BOT_is_first_position_long

#include "lib/utils/io.cpp" // ::utils::io
#include "tao_bot.h"        // Alpaca::TaoBot
#include <ctime>            // std::localtime, std::time, std::time_t
#include <string>           // std::string
#include <vector>           // std::vector

bool Alpaca::TaoBot::is_first_position_long() {
  std::vector<std::string> symbols = ::utils::io::tradeable_symbols("alpaca");
  int index = 0;
  int i = 0;

  for (std::vector<std::string>::iterator it = symbols.begin();
       it != symbols.end(); it++, i++) {
    if (*it == std::string(this->symbol)) {
      index = i;
      break;
    }
  }

  const int is_index_even = index % 2 == 0;
  std::time_t local_now;
  std::time(&local_now);
  std::tm local_time = *std::localtime(&local_now);

  return (local_time.tm_mday + local_time.tm_min + is_index_even) % 2 == 0;
}

#endif
