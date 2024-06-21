// TODO: Decide
#ifndef ALPACA__TAO_BOT_build_day_candle
#define ALPACA__TAO_BOT_build_day_candle

#include "current_mid.cpp" // current_mid
#include "tao_bot.h"       // Alpaca::TaoBot
#include <valarray>        // std::valarray

void Alpaca::TaoBot::build_day_candle() {
  const double mid = current_mid();

  this->day_candle.close = mid;
  this->day_candle.closed_at = this->current_epoch;

  for (const candle_t candle : this->latest_candles) {
    this->day_candle.open =
        this->day_candle.open ? this->day_candle.open : candle.open;

    this->day_candle.opened_at = this->day_candle.opened_at
                                     ? this->day_candle.opened_at
                                     : candle.opened_at;

    std::valarray<double> highs = {this->day_candle.high, candle.high, mid};
    std::valarray<double> lows = {this->day_candle.low, candle.low, mid};

    this->day_candle.high = highs.max();
    this->day_candle.low = lows.min();
  }
}

#endif
