// TODO: Decide
#ifndef OANDA__TAO_BOT_spike_score
#define OANDA__TAO_BOT_spike_score

#include "tao_bot.h" // Oanda::TaoBot, spike_candles_t
#include <math.h>    // INFINITY

double Oanda::TaoBot::spike_score(spike_candles_t candles) {
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
