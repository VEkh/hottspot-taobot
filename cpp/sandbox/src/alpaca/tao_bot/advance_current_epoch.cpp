#ifndef ALPACA__TAO_BOT_advance_current_epoch
#define ALPACA__TAO_BOT_advance_current_epoch

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::max
#include <string>    // std::stod, std::string
#include <time.h>    // time
#include <unistd.h>  // usleep

void Alpaca::TaoBot::advance_current_epoch() {
  if (this->backtest.is_active) {
    const double clock_tick_seconds = 1.0;

    if (this->tradeable_symbols_count == 1 ||
        !this->backtest.config.clock_sync) {
      advance_current_epoch(this->current_epoch + clock_tick_seconds);
    } else {

      this->backtest.publish_clock(this->current_epoch);

      const std::string sibling_epoch_string = this->backtest.subscribe_clock();

      const double sibling_epoch =
          sibling_epoch_string.empty() ? 0 : std::stod(sibling_epoch_string);

      if (sibling_epoch < this->current_epoch) {
        return advance_current_epoch();
      }

      const double new_epoch =
          std::max(this->current_epoch + clock_tick_seconds, sibling_epoch);

      advance_current_epoch(new_epoch);
    }

    this->backtest.slow_query_countdown += 1;
  } else {
    usleep(5e5);

    advance_current_epoch(time(nullptr));
  }
}

void Alpaca::TaoBot::advance_current_epoch(const double epoch) {
  this->current_epoch = epoch;
}

#endif
