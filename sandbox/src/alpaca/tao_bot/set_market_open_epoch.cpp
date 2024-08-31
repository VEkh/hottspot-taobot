#ifndef ALPACA__CLIENT_set_market_open_epoch
#define ALPACA__CLIENT_set_market_open_epoch

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::set_market_open_epoch() {
  this->market_open_epoch =
      this->market_availability.market_open_epoch(this->current_epoch);
}

#endif
