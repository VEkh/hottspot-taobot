#ifndef ALPACA__TAO_BOT_tradeable_symbols_count
#define ALPACA__TAO_BOT_tradeable_symbols_count

#include "lib/utils/io.cpp" // ::utils::io
#include "tao_bot.h"        // Alpaca::TaoBot

int Alpaca::TaoBot::tradeable_symbols_count() {
  std::vector<std::string> symbols = ::utils::io::tradeable_symbols("alpaca");

  return symbols.size();
}

#endif
