#ifndef ALPACA__TAO_BOT_is_market_open
#define ALPACA__TAO_BOT_is_market_open

#include "alpaca/utils.cpp" // Alpaca::Utils
#include "tao_bot.h"        // Alpaca::TaoBot

bool Alpaca::TaoBot::is_market_open() {
  return Alpaca::Utils::is_market_open(
      this->current_epoch, this->api_client.config.late_start_seconds);
}

#endif
