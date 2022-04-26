#ifndef ALPACA__TAO_BOT_converted_signaler_price
#define ALPACA__TAO_BOT_converted_signaler_price

#include "current_price.cpp" // current_price
#include "tao_bot.h"         // Alpaca::TaoBot, signal_t

double Alpaca::TaoBot::converted_signaler_price(const signal_t &signal) {
  if (signal.signaler.empty()) {
    return 0.00;
  }

  return current_price(signal.signaler) *
         signal.signaled_to_signaler_price_ratio;
}

#endif
