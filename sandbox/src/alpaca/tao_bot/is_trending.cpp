#ifndef ALPACA__CLIENT_is_trending
#define ALPACA__CLIENT_is_trending

#include "tao_bot.h" // Alpaca::TaoBot, trend_meta_t, trend_t

bool Alpaca::TaoBot::is_trending() { return is_trending(this->current_trend); }

bool Alpaca::TaoBot::is_trending(const trend_meta_t trend_meta) {
  if (trend_meta.trend == trend_t::TREND_CONSOLIDATION) {
    return false;
  }

  return true;
}

#endif
