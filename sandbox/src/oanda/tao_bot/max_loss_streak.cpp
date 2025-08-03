// TODO: Decide
#ifndef OANDA__TAO_BOT_max_loss_streak
#define OANDA__TAO_BOT_max_loss_streak

#include "execution_strategy.cpp" // execution_strategy
#include "tao_bot.h"              // Oanda::TaoBot

int Oanda::TaoBot::max_loss_streak() {
  const int config = this->api_client.config.max_loss_streak;

  const int dynamic_max_loss_streak =
      this->api_client.config.dynamic_max_loss_streak;

  if (!dynamic_max_loss_streak) {
    return config;
  }

  // v0.1
  if (execution_strategy() == execution_strategy_t::EXECUTION_STRATEGY_TREND) {
    return dynamic_max_loss_streak;
  }

  return config;
}

#endif
