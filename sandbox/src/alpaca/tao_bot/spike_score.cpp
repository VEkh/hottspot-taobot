// TODO: Decide
#ifndef ALPACA__TAO_BOT_spike_score
#define ALPACA__TAO_BOT_spike_score

#include "tao_bot.h" // Alpaca::TaoBot, spike_candles_t
#include <math.h>    // INFINITY

double Alpaca::TaoBot::spike_score(spike_candles_t candles) {
  if (!candles.current.opened_at) {
    return 0.0;
  }

  if (!candles.previous.opened_at) {
    return 0.0;
  }

  const double score = candles.current.range() / candles.previous.range();

  return score == INFINITY ? 0.0 : score;
}

#endif
