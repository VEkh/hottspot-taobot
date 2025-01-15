#ifndef ALPACA__TAO_BOT_build_reversals
#define ALPACA__TAO_BOT_build_reversals

#include "tao_bot.h" // Alpaca::TaoBot, candle_t, reversal_t, reversal_type_t
#include <algorithm> // std::max, std::min
#include <iterator>  // std::next, std::prev
#include <list>      // std::list
#include <math.h>    // INFINITY, abs

void Alpaca::TaoBot::build_reversals(reversals_t &reversals_,
                                     const bool enforce_symmetry = false) {
  const int timeframe_minutes = reversals_.timeframe_minutes;

  if (!timeframe_minutes) {
    return;
  }

  if (this->latest_candles.empty()) {
    return;
  }

  const bool are_reversals_updated =
      reversals_.candles_count == this->latest_candles.size();

  if (are_reversals_updated) {
    return;
  }

  reversals_.highs = {};
  reversals_.lows = {};
  reversals_.record_counts = {{"highs", 0}, {"lows", 0}};

  const double start_epoch = this->market_availability.market_epochs.open;

  double running_record_high = -INFINITY;
  double running_record_low = INFINITY;

  const int end_opened_at_minute = this->latest_candles.back().opened_at / 60;
  const int seek_minutes = timeframe_minutes / 2;

  candle_t begin_candle;
  std::list<candle_t>::iterator it;
  std::list<candle_t>::iterator peek_ahead;
  std::list<candle_t>::iterator peek_behind;

  for (it = this->latest_candles.begin(); it != this->latest_candles.end();
       it++) {
    if (it->opened_at < start_epoch) {
      continue;
    }

    if (!begin_candle.opened_at) {
      begin_candle = *it;
    }

    const int opened_at_minute = it->opened_at / 60;

    const int end_delta_minutes = abs(opened_at_minute - end_opened_at_minute);

    const bool near_end = end_delta_minutes < seek_minutes;

    if (near_end) {
      continue;
    }

    if (enforce_symmetry) {
      const int begin_opened_at_minute = begin_candle.opened_at / 60;

      const int begin_delta_minutes =
          abs(opened_at_minute - begin_opened_at_minute);

      const bool near_begin = begin_delta_minutes < seek_minutes;

      if (near_begin) {
        continue;
      }
    }

    bool is_high = true;
    bool is_low = true;

    double high = it->high;
    double low = it->low;

    peek_ahead = std::next(it, 0);
    peek_behind = std::next(it, 0);

    while (true) {
      peek_ahead = std::next(peek_ahead, 1);

      if (peek_ahead == this->latest_candles.end()) {
        break;
      }

      const int peek_minute = peek_ahead->opened_at / 60;
      const int peek_delta_minutes = abs(peek_minute - opened_at_minute);

      if (peek_delta_minutes > seek_minutes) {
        break;
      }

      double next_high = peek_ahead->high;
      double next_low = peek_ahead->low;

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

    while (true) {
      peek_behind = std::prev(peek_behind, 1);

      const int peek_minute = peek_behind->opened_at / 60;
      const int peek_delta_minutes = abs(peek_minute - opened_at_minute);

      if (peek_delta_minutes > seek_minutes) {
        break;
      }

      double next_high = peek_behind->high;
      double next_low = peek_behind->low;

      if (next_high >= high) {
        is_high = false;
      }

      if (next_low <= low) {
        is_low = false;
      }

      if (!next_high && !next_low) {
        break;
      }

      if (peek_behind == this->latest_candles.begin()) {
        break;
      }
    }

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

  reversals_.candles_count = (int)this->latest_candles.size();
}

#endif
