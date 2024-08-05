#ifndef ALPACA__CLIENT_set_market_close_epoch
#define ALPACA__CLIENT_set_market_close_epoch

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // set_market_close_epoch
#include <string>             // std::string

void Alpaca::TaoBot::set_market_close_epoch() {
  this->market_close_epoch =
      this->market_availability.market_close_epoch(this->current_epoch);
}

#endif
