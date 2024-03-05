// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_within_entry_window
#define ALPACA__TAO_BOT_is_within_entry_window

#include "current_mid.cpp" // current_mid
#include "tao_bot.h"       // Alpaca::TaoBot, reversal_t
#include <math.h>          // abs

bool Alpaca::TaoBot::is_within_entry_window(const reversal_t reversal) {
  const double mid = current_mid();
  const double static_one_sec_variance = this->avg_one_sec_variances.running;
  const double stop_loss_ratio = this->api_client.config.stop_loss_ratio;

  const double entry_window = abs(stop_loss_ratio * static_one_sec_variance);

  const double reversal_delta = abs(reversal.mid - mid);

  return reversal_delta <= entry_window;
}

#endif
