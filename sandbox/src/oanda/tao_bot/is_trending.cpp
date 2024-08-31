#ifndef OANDA__CLIENT_is_trending
#define OANDA__CLIENT_is_trending

#include "tao_bot.h" // Oanda::TaoBot, trend_meta_t, trend_t

bool Oanda::TaoBot::is_trending() { return is_trending(this->current_trend); }

bool Oanda::TaoBot::is_trending(const trend_meta_t trend_meta) {
  if (trend_meta.trend == trend_t::TREND_CONSOLIDATION) {
    return false;
  }

  return true;
}

#endif
