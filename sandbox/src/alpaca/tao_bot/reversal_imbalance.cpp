// TODO: Decide
#ifndef ALPACA__TAO_BOT_reversal_imbalance
#define ALPACA__TAO_BOT_reversal_imbalance

#include "tao_bot.h" // Alpaca::TaoBot

Alpaca::TaoBot::trend_t Alpaca::TaoBot::reversal_imbalance() {
  const int lows_n = this->reversals.lows.size();
  const int highs_n = this->reversals.highs.size();

  if (lows_n == highs_n) {
    return trend_t::TREND_CONSOLIDATION;
  }

  if (lows_n > highs_n) {
    return trend_t::TREND_UP;
  }

  return trend_t::TREND_DOWN;
}

#endif
