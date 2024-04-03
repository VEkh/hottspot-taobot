// TODO: Delete when finalizing single loss trend
#ifndef ALPACA__CLIENT_is_trend_indicating_loss
#define ALPACA__CLIENT_is_trend_indicating_loss

#include "tao_bot.h" // Alpaca::TaoBot, order_t

bool Alpaca::TaoBot::is_trend_indicating_loss(const position_t position) {
  if (position.close_order.profit > 0) {
    return false;
  }

  if (position.open_order.is_trending) {
    return false;
  }

  return true;
}

#endif
