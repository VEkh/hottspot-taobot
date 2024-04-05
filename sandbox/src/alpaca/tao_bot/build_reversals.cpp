#ifndef ALPACA__TAO_BOT_build_reversals
#define ALPACA__TAO_BOT_build_reversals

#include "current_mid.cpp" // current_mid
#include "tao_bot.h" // Alpaca::TaoBot, candle_t, reversal_t, reversal_type_t
#include <algorithm> // std::max, std::min
#include <list>      // std::list
#include <math.h>    // INFINITY, abs, floor

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
  reversals_.record_counts = {{"highs", 0}, {"lows", 0}};

  const double start_epoch = this->market_open_epoch;

  double running_record_high = -INFINITY;
  double running_record_low = INFINITY;

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
      running_record_high = std::max(running_record_high, high);

      reversals_.highs[it->opened_at] = {
          .at = it->opened_at,
          .is_record = false,
          .is_running_record = false,
          .mid = high,
          .timeframe_minutes = timeframe_minutes,
          .type = reversal_type_t::REVERSAL_HIGH,
      };
    }

    if (is_low) {
      running_record_low = std::min(running_record_low, low);

      reversals_.lows[it->opened_at] = {
          .at = it->opened_at,
          .is_record = false,
          .is_running_record = false,
          .mid = low,
          .timeframe_minutes = timeframe_minutes,
          .type = reversal_type_t::REVERSAL_LOW,
      };
    }
  }

  double record_high = -INFINITY;
  double record_low = INFINITY;
  std::list<double> record_high_epochs;
  std::list<double> record_low_epochs;
  std::map<double, reversal_t>::iterator r_it;

  for (r_it = reversals_.highs.begin(); r_it != reversals_.highs.end();
       r_it++) {
    record_high = std::max(record_high, r_it->second.mid);

    if (r_it->second.mid == record_high) {
      record_high_epochs.push_back(r_it->second.at);
      reversals_.record_counts["highs"]++;

      r_it->second.is_record = true;
    }

    if (r_it->second.mid == running_record_high) {
      r_it->second.is_running_record = true;
    }
  }

  for (r_it = reversals_.lows.begin(); r_it != reversals_.lows.end(); r_it++) {
    record_low = std::min(record_low, r_it->second.mid);

    if (r_it->second.mid == record_low) {
      record_low_epochs.push_back(r_it->second.at);
      reversals_.record_counts["lows"]++;

      r_it->second.is_record = true;
    }

    if (r_it->second.mid == running_record_low) {
      r_it->second.is_running_record = true;
    }
  }

  std::list<double>::reverse_iterator epoch_it;

  for (epoch_it = record_high_epochs.rbegin();
       epoch_it != record_high_epochs.rend(); epoch_it++) {
    if (std::next(epoch_it) == record_high_epochs.rend()) {
      break;
    }

    const double next_epoch = *std::next(epoch_it);
    const double epoch_delta = abs(*epoch_it - next_epoch);
  }

  for (epoch_it = record_low_epochs.rbegin();
       epoch_it != record_low_epochs.rend(); epoch_it++) {
    if (std::next(epoch_it) == record_low_epochs.rend()) {
      break;
    }

    const double next_epoch = *std::next(epoch_it);
    const double epoch_delta = abs(*epoch_it - next_epoch);
  }

  reversals_.updated_at = this->latest_candles.back().closed_at;
}

#endif
