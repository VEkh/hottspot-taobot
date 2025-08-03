// TODO: Decide
#ifndef OANDA__TAO_BOT_stop_profit_version
#define OANDA__TAO_BOT_stop_profit_version

#include "execution_strategy.cpp" // execution_strategy
#include "tao_bot.h"              // Oanda::TaoBot, execution_strategy_t

double Oanda::TaoBot::stop_profit_version() {
  const double config = this->api_client.config.stop_profit_version;
  const double limit =
      this->api_client.config.dynamic_stop_profit_version_limit;

  if (!limit) {
    return config;
  }

  if (execution_strategy() ==
      execution_strategy_t::EXECUTION_STRATEGY_CONSOLIDATION) {
    return 0.1;
  }

  // v0.1
  if (this->warm_up_candle.range_open_percent() <= limit) {
    return config;
  }

  return 0.1;
}

#endif
