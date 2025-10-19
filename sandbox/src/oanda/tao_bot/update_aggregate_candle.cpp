#ifndef OANDA__TAO_BOT_update_aggregate_candle
#define OANDA__TAO_BOT_update_aggregate_candle

#include "tao_bot.h" // Oanda::TaoBot
#include <algorithm> // std::max, std::min

void Oanda::TaoBot::update_aggregate_candle(candle_t &agg_candle,
                                            const candle_t candle) {
  agg_candle.close = candle.close;
  agg_candle.closed_at = candle.closed_at;

  agg_candle.open = agg_candle.open ? agg_candle.open : candle.open;

  agg_candle.opened_at =
      agg_candle.opened_at ? agg_candle.opened_at : candle.opened_at;

  agg_candle.high = std::max(agg_candle.high, candle.high);
  agg_candle.low = std::min(agg_candle.low, candle.low);

  if (agg_candle.high == candle.high) {
    agg_candle.high_at = candle.opened_at;
  }

  if (agg_candle.low == candle.low) {
    agg_candle.low_at = candle.opened_at;
  }
}

#endif
