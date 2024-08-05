#ifndef ALPACA__CLIENT_set_market_open_epoch
#define ALPACA__CLIENT_set_market_open_epoch

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot
#include <string>             // std::string

void Alpaca::TaoBot::set_market_open_epoch() {
  this->market_open_epoch =
      this->market_availability.market_open_epoch(this->current_epoch);
}

#endif
