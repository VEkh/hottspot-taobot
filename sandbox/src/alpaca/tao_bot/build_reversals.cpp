// TODO: Decide
#ifndef ALPACA__TAO_BOT_build_reversals
#define ALPACA__TAO_BOT_build_reversals

#include "current_mid.cpp" // current_mid
#include "tao_bot.h" // Alpaca::TaoBot, candle_t, reversal_t, reversal_type_t
#include <algorithm> // std::max, std::min
#include <list>      // std::list
#include <math.h>    // INFINITY, floor

void Alpaca::TaoBot::build_reversals(reversals_t &reversals_) {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return;
  }

  const int timeframe_minutes = reversals_.timeframe_minutes;

  if (!timeframe_minutes) {
    return;
  }

  if (this->latest_candles.empty()) {
    return;
  }

  const bool are_reversals_updated =
      floor(reversals_.updated_at / 60) == floor(this->current_epoch / 60);

  if (are_reversals_updated) {
    return;
  }

  reversals_.highs = {};
  reversals_.lows = {};

  const double candles_timeframe_minutes =
      this->api_client.config.candles_timeframe_minutes;

  const double start_epoch =
      candles_timeframe_minutes
          ? std::max(this->market_open_epoch,
                     this->current_epoch - candles_timeframe_minutes * 60)
          : this->market_open_epoch;

  double record_high = -INFINITY;
  double record_low = INFINITY;

  const int seek_n = timeframe_minutes / 2;

  int i = 0;
  std::list<candle_t>::iterator it;

  for (it = this->latest_candles.begin(); it != this->latest_candles.end();
       it++, i++) {
    if (it->opened_at < start_epoch) {
      continue;
    }

    bool near_end = false;
    int end_seek_n = 1;

    while (end_seek_n <= seek_n) {
      if (std::next(it, end_seek_n) == this->latest_candles.end()) {
        near_end = true;
        break;
      }

      end_seek_n++;
    }

    if (near_end) {
      continue;
    }

    bool is_high = true;
    bool is_low = true;

    double high = it->high;
    double low = it->low;

    int back_seek_i = 0;
    int front_seek_i = 0;

    for (; it != this->latest_candles.end() && front_seek_i < seek_n;
         front_seek_i++) {
      std::advance(it, 1);

      double next_high = it->high;
      double next_low = it->low;

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

      double next_high = it->high;
      double next_low = it->low;

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
      record_high = std::max(record_high, high);
      reversals_.highs[it->opened_at] = {
          .at = it->opened_at,
          .is_record = false,
          .mid = high,
          .timeframe_minutes = timeframe_minutes,
          .type = reversal_type_t::REVERSAL_HIGH,
      };
    }

    if (is_low) {
      record_low = std::min(record_low, low);
      reversals_.lows[it->opened_at] = {
          .at = it->opened_at,
          .is_record = false,
          .mid = low,
          .timeframe_minutes = timeframe_minutes,
          .type = reversal_type_t::REVERSAL_LOW,
      };
    }
  }

  std::map<double, reversal_t>::reverse_iterator r_it;

  for (r_it = reversals_.highs.rbegin(); r_it != reversals_.highs.rend();
       r_it++) {
    if (r_it->second.mid == record_high) {
      r_it->second.is_record = true;

      break;
    }
  }

  for (r_it = reversals_.lows.rbegin(); r_it != reversals_.lows.rend();
       r_it++) {
    if (r_it->second.mid == record_low) {
      r_it->second.is_record = true;

      break;
    }
  }

  reversals_.updated_at = this->latest_candles.back().closed_at;
}

#endif
