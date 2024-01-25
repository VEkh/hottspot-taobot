// TODO: Decide
#ifndef ALPACA__TAO_BOT_build_reversals
#define ALPACA__TAO_BOT_build_reversals

#include "current_mid.cpp" // current_mid
#include "tao_bot.h"       // Alpaca::TaoBot, candle_t
#include <algorithm>       // std::max, std::min
#include <list>            // std::list
#include <math.h>          // INFINITY, floor

void Alpaca::TaoBot::build_reversals() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return;
  }

  const bool are_reversals_updated =
      floor(this->reversals.updated_at / 60) == floor(this->current_epoch / 60);

  if (are_reversals_updated) {
    return;
  }

  this->reversals.highs = {};
  this->reversals.lows = {};

  const int duration_minutes =
      this->api_client.config.consolidation_duration_mintues;
  const int seek_n = duration_minutes / 2;
  int i = 0;
  std::list<candle_t>::iterator it;

  for (it = this->latest_candles.begin(); it != this->latest_candles.end();
       it++, i++) {
    bool is_high = true;
    bool is_low = true;

    double high = std::max(it->close, it->open);
    double low = std::min(it->close, it->open);

    int back_seek_i = 0;
    int front_seek_i = 0;

    if (this->current_epoch - it->opened_at < duration_minutes * 60) {
      continue;
    }

    for (; it != this->latest_candles.end() && front_seek_i < seek_n;
         front_seek_i++) {
      std::advance(it, 1);

      double next_high = std::max(it->close, it->open);
      double next_low = std::min(it->close, it->open);

      if (next_high > high) {
        is_high = false;
      }

      if (next_low < low) {
        is_low = false;
      }

      if (!next_high && !next_low) {
        break;
      }
    }

    std::advance(it, -front_seek_i);

    for (; it != this->latest_candles.begin() && back_seek_i < seek_n;
         back_seek_i++) {
      std::advance(it, -1);

      double next_high = std::max(it->close, it->open);
      double next_low = std::min(it->close, it->open);

      if (next_high >= high) {
        is_high = false;
      }

      if (next_low <= low) {
        is_low = false;
      }

      if (!next_high && !next_low) {
        break;
      }
    }

    std::advance(it, back_seek_i);

    if (is_high) {
      this->reversals.highs[it->opened_at] = high;
    }

    if (is_low) {
      this->reversals.lows[it->opened_at] = low;
    }
  }

  this->reversals.updated_at = this->latest_candles.back().opened_at;
}

#endif
