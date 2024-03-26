#ifndef ALPACA__CLIENT_is_trending
#define ALPACA__CLIENT_is_trending

#include "tao_bot.h" // Alpaca::TaoBot, trend_t

bool Alpaca::TaoBot::is_trending() {
  if (this->current_trend.trend == trend_t::TREND_CONSOLIDATION) {
    return false;
  }

  return true;
}

#endif
