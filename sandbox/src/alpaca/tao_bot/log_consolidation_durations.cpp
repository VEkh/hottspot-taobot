#ifndef ALPACA__TAO_BOT_log_consolidation_durations
#define ALPACA__TAO_BOT_log_consolidation_durations

#include "log_consolidation_duration.cpp" // log_consolidation_duration
#include "tao_bot.h"                      // Alpaca::TaoBot

void Alpaca::TaoBot::log_consolidation_durations() {
  if (!this->api_client.config.should_await_consolidation_indicator) {
    return;
  }

  log_consolidation_duration();
}

#endif
