// TODO: Decide
#ifndef ALPACA__TAO_BOT_should_invert_reversal
#define ALPACA__TAO_BOT_should_invert_reversal

#include "tao_bot.h" // Alpaca::TaoBot, reversal_t

bool Alpaca::TaoBot::should_invert_reversal(const reversal_t reversal) {
  const double invert_threshold =
      this->api_client.config.conditional_invert_ratio *
      this->day_candle.range();

  bool should_invert = false;

  for (const candle_t candle : this->latest_candles) {
    if (should_invert) {
      break;
    }

    if (candle.opened_at < reversal.at) {
      continue;
    }

    if (candle.opened_at >= this->current_epoch) {
      break;
    }

    double delta;

    if (reversal.type == reversal_type_t::REVERSAL_HIGH) {
      delta = abs(reversal.mid - candle.low);
    } else if (reversal.type == reversal_type_t::REVERSAL_LOW) {
      delta = abs(reversal.mid - candle.high);
    }

    should_invert = delta >= invert_threshold;
  }

  return should_invert;
}

#endif
