// TODO: Decide
#ifndef ALPACA__CLIENT_is_trend_indicating_loss
#define ALPACA__CLIENT_is_trend_indicating_loss

#include "tao_bot.h" // Alpaca::TaoBot, order_t

bool Alpaca::TaoBot::is_trend_indicating_loss(const position_t position) {
  if (position.close_order.profit > 0) {
    return false;
  }

  const double static_one_sec_variance = this->avg_one_sec_variances.running;

  return position.open_order.max_profit < 10 * static_one_sec_variance;
}

#endif
