#ifndef DB__PRICE_ACTION_process_quotes
#define DB__PRICE_ACTION_process_quotes

#include "log_build_summary.cpp" // log_build_summary
#include "log_candle.cpp"        // log_candle
#include "price_action.h"        // DB::PriceAction, candle_t, quote_t
#include "update_avg.cpp"        // update_avg
#include "upsert.cpp"            // upsert
#include <algorithm>             // std::max, std::min

void DB::PriceAction::process_quotes() {
  for (const quote_t quote : this->build_state.quotes) {
    if (!this->market_availability.is_market_open(quote.timestamp)) {
      continue;
    }

    if (this->build_state.day_candle.closed_at &&
        quote.timestamp > this->build_state.day_candle.closed_at) {
      upsert(this->build_state.day_candle);
      update_avg(this->build_state);
      log_candle(this->build_state.day_candle);
      log_build_summary(this->build_state);

      this->build_state.day_candle = candle_t();

      if (!this->market_availability.is_market_open(quote.timestamp)) {
        continue;
      }
    }

    if (!this->build_state.day_candle.opened_at) {
      this->build_state.day_candle.closed_at =
          this->market_availability.market_close_epoch(quote.timestamp);

      this->build_state.day_candle.opened_at =
          this->market_availability.market_open_epoch(quote.timestamp);
    }

    const double mid = quote.mid();

    this->build_state.day_candle.close = mid;

    this->build_state.day_candle.open = this->build_state.day_candle.open
                                            ? this->build_state.day_candle.open
                                            : mid;

    this->build_state.day_candle.high =
        std::max(this->build_state.day_candle.high, mid);

    this->build_state.day_candle.low =
        std::min(this->build_state.day_candle.low, mid);

    if (this->build_state.day_candle.high == mid) {
      this->build_state.day_candle.high_at = quote.timestamp;
    }

    if (this->build_state.day_candle.low == mid) {
      this->build_state.day_candle.low_at = quote.timestamp;
    }
  }

  upsert(this->build_state.day_candle);
  update_avg(this->build_state);
  log_candle(this->build_state.day_candle);
  log_build_summary(this->build_state);
}

#endif
