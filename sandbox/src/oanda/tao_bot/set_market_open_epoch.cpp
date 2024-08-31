#ifndef OANDA__CLIENT_set_market_open_epoch
#define OANDA__CLIENT_set_market_open_epoch

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::set_market_open_epoch() {
  this->market_open_epoch =
      this->market_availability.market_open_epoch(this->current_epoch);
}

#endif
