#ifndef OANDA__TAO_BOT_is_first_position_long
#define OANDA__TAO_BOT_is_first_position_long

#include "lib/utils/io.cpp" // ::utils::io
#include "tao_bot.h"        // Oanda::TaoBot
#include <ctime>            // std::localtime, std::time, std::time_t
#include <list>             // std::list
#include <string>           // std::string

bool Oanda::TaoBot::is_first_position_long() {
  std::list<std::string> symbols = ::utils::io::tradeable_symbols("oanda");
  int index = 0;
  int i = 0;

  for (std::list<std::string>::iterator it = symbols.begin();
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
