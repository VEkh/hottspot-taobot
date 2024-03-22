#ifndef ALPACA__TAO_BOT_volatility
#define ALPACA__TAO_BOT_volatility

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::min

double Alpaca::TaoBot::volatility(const bool is_gated = false) {
  if (!this->avg_one_sec_variances.running) {
    return 0.0;
  }

  const double volatility_ =
      this->avg_one_sec_variances.latest / this->avg_one_sec_variances.running;

  if (!is_gated) {
    return volatility_;
  }

  return std::min(volatility_, 1.0);
}

#endif
