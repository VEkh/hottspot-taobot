#ifndef ALPACA__TAO_BOT_is_in_win_percentile
#define ALPACA__TAO_BOT_is_in_win_percentile

#include "day_range_percentile.cpp" // day_range_percentile
#include "tao_bot.h"                // Alpaca::TaoBot, order_t
#include <string>                   // std::string

bool Alpaca::TaoBot::is_in_win_percentile(const order_t *order,
                                          const double profit) {
  if (!this->api_client.config.win_percentile) {
    return false;
  }

  if (!order) {
    return false;
  }

  if (profit < 0) {
    return false;
  }

  return day_range_percentile(order, profit) >=
         this->api_client.config.win_percentile;
}

#endif
