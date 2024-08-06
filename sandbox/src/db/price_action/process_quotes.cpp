#ifndef DB__PRICE_ACTION_process_quotes
#define DB__PRICE_ACTION_process_quotes

#include "log_day_candle.cpp" // log_day_candle
#include "price_action.h"     // DB::PriceAction, candle_t, quote_t
#include "update_avg.cpp"     // update_avg
#include <algorithm>          // std::max, std::min

void DB::PriceAction::process_quotes() {
  for (const quote_t quote : this->quotes) {
    if (!this->market_availability.is_market_open(quote.timestamp)) {
      continue;
    }

    if (this->day_candle.closed_at &&
        quote.timestamp > this->day_candle.closed_at) {
      update_avg();
      log_day_candle();

      this->day_candle = candle_t();

      if (!this->market_availability.is_market_open(quote.timestamp)) {
        continue;
      }
    }

    if (!this->day_candle.opened_at) {
      this->day_candle.closed_at =
          this->market_availability.market_close_epoch(quote.timestamp);

      this->day_candle.opened_at =
          this->market_availability.market_open_epoch(quote.timestamp);
    }

    const double mid = quote.mid();

    this->day_candle.close = mid;

    this->day_candle.open = this->day_candle.open ? this->day_candle.open : mid;

    this->day_candle.high = std::max(this->day_candle.high, mid);
    this->day_candle.low = std::min(this->day_candle.low, mid);

    if (this->day_candle.high == mid) {
      this->day_candle.high_at = quote.timestamp;
    }

    if (this->day_candle.low == mid) {
      this->day_candle.low_at = quote.timestamp;
    }
  }
}

#endif
