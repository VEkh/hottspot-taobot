#ifndef ALPACA__TAO_BOT_read_price_movement
#define ALPACA__TAO_BOT_read_price_movement

#include "should_backtest_exec_slow_query.cpp" // should_backtest_exec_slow_query
#include "tao_bot.h"                           // Alpaca::TaoBot

void Alpaca::TaoBot::read_price_movement() {
  if (!should_backtest_exec_slow_query()) {
    return;
  }

  this->one_sec_variance_avgs =
      this->quoter.db_quote.get_one_sec_variance_avgs({
          .symbol = this->symbol,
          .timestamp_upper_bound = this->api_client.config.current_epoch,
      });
}

#endif
