#ifndef ALPACA__TAO_BOT_advance_current_epoch
#define ALPACA__TAO_BOT_advance_current_epoch

#include "tao_bot.h"                   // Alpaca::TaoBot
#include "tradeable_symbols_count.cpp" // tradeable_symbols_count
#include <time.h>                      // time
#include <unistd.h>                    // usleep

void Alpaca::TaoBot::advance_current_epoch() {
  if (this->backtest.is_active) {
    this->backtest.db_backtest_clock.upsert({
        .api_key_id = this->backtest.config.api_key_id,
        .set_to = this->current_epoch,
        .symbol = this->symbol,
    });

    const int backtest_clocks_count =
        this->backtest.db_backtest_clock
            .get_all({
                .api_key_id = this->backtest.config.api_key_id,
                .set_to = this->current_epoch,
            })
            .size();

    if (backtest_clocks_count < tradeable_symbols_count()) {
      return advance_current_epoch();
    }

    advance_current_epoch(this->current_epoch + 1);
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
