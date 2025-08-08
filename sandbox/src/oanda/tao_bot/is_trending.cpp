#ifndef OANDA__CLIENT_is_trending
#define OANDA__CLIENT_is_trending

#include "tao_bot.h" // Oanda::TaoBot, trend_t

bool Oanda::TaoBot::is_trending() {
  if (this->current_trend.trend == trend_t::TREND_CONSOLIDATION) {
    return false;
  }

  return true;
}

#endif
