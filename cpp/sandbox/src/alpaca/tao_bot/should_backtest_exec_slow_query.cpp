#ifndef ALPACA__TAO_BOT_should_backtest_exec_slow_operation
#define ALPACA__TAO_BOT_should_backtest_exec_slow_operation

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::should_backtest_exec_slow_query() {
  if (!this->api_client.config.is_backtest) {
    return true;
  }

  return this->api_client.backtest_config.slow_query_countdown %
             this->api_client.backtest_config.SLOW_QUERY_EVERY ==
         0;
}

#endif
