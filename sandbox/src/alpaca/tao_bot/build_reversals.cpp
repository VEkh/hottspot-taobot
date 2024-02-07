// TODO: Decide
#ifndef ALPACA__TAO_BOT_build_reversals
#define ALPACA__TAO_BOT_build_reversals

#include "current_mid.cpp"      // current_mid
#include "db/candle/candle.cpp" // DB::Candle
#include "tao_bot.h" // Alpaca::TaoBot, candle_t, reversal_t, reversal_type_t
#include <algorithm> // std::max, std::min
#include <list>      // std::list
#include <math.h>    // INFINITY, floor

void Alpaca::TaoBot::build_reversals() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return;
  }

  if (this->latest_candles.empty()) {
    return;
  }

  DB::Candle::candle_bounds_t epoch_bounds =
      DB::Candle::timestamp_to_bounds(1, this->current_epoch);

  const bool are_candles_stale =
      epoch_bounds.opened_at != this->latest_candles.back().closed_at;

  if (are_candles_stale) {
    return;
  }

  const bool are_reversals_updated =
      floor(this->reversals.updated_at / 60) == floor(this->current_epoch / 60);

  if (are_reversals_updated) {
    return;
  }

  this->reversals.highs = {};
  this->reversals.lows = {};

  const double candles_timeframe_minutes =
      this->api_client.config.candles_timeframe_minutes;

  const int duration_minutes =
      this->api_client.config.reversal_timeframe_minutes;

  const double start_epoch =
      candles_timeframe_minutes
          ? std::max(this->market_open_epoch,
                     this->current_epoch - candles_timeframe_minutes * 60)
          : this->market_open_epoch;

  double record_high = -INFINITY;
  double record_low = INFINITY;

  const int seek_n = duration_minutes / 2;

  int i = 0;
  std::list<candle_t>::iterator it;

  for (it = this->latest_candles.begin(); it != this->latest_candles.end();
       it++, i++) {
    if (it->opened_at < start_epoch) {
      continue;
    }

    bool is_high = true;
    bool is_low = true;

    double high = it->high;
    double low = it->low;

    int back_seek_i = 0;
    int front_seek_i = 0;

    if (this->current_epoch - it->opened_at < seek_n * 60) {
      continue;
    }

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
      this->reversals.highs[it->opened_at] = {
          .at = it->opened_at,
          .is_record = false,
          .mid = high,
          .type = reversal_type_t::REVERSAL_HIGH,
      };
    }

    if (is_low) {
      record_low = std::min(record_low, low);
      this->reversals.lows[it->opened_at] = {
          .at = it->opened_at,
          .is_record = false,
          .mid = low,
          .type = reversal_type_t::REVERSAL_LOW,
      };
    }
  }

  std::map<double, reversal_t>::reverse_iterator r_it;

  for (r_it = this->reversals.highs.rbegin();
       r_it != this->reversals.highs.rend(); r_it++) {
    if (r_it->second.mid == record_high) {
      r_it->second.is_record = true;

      break;
    }
  }

  for (r_it = this->reversals.lows.rbegin();
       r_it != this->reversals.lows.rend(); r_it++) {
    if (r_it->second.mid == record_low) {
      r_it->second.is_record = true;

      break;
    }
  }

  this->reversals.updated_at = this->latest_candles.back().opened_at;
}

#endif
