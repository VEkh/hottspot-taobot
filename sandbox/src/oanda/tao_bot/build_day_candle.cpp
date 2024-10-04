#ifndef OANDA__TAO_BOT_build_day_candle
#define OANDA__TAO_BOT_build_day_candle

#include "tao_bot.h" // Oanda::TaoBot, candle_t
#include <algorithm> // std::max, std::min

void Oanda::TaoBot::build_day_candle() {
  for (const candle_t candle : this->latest_candles) {
    if (candle.opened_at > this->current_epoch) {
      break;
    }

    this->day_candle.close = candle.close;
    this->day_candle.closed_at = candle.closed_at;

    this->day_candle.open =
        this->day_candle.open ? this->day_candle.open : candle.open;

    this->day_candle.opened_at = this->day_candle.opened_at
                                     ? this->day_candle.opened_at
                                     : candle.opened_at;

    this->day_candle.high = std::max(this->day_candle.high, candle.high);
    this->day_candle.low = std::min(this->day_candle.low, candle.low);

    if (this->day_candle.high == candle.high) {
      this->day_candle.high_at = candle.opened_at;
    }

    if (this->day_candle.low == candle.low) {
      this->day_candle.low_at = candle.opened_at;
    }
  }
}

#endif
