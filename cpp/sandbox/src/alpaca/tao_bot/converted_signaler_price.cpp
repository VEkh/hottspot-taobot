#ifndef ALPACA__TAO_BOT_converted_signaler_price
#define ALPACA__TAO_BOT_converted_signaler_price

#include "current_price.cpp" // current_price
#include "tao_bot.h"         // Alpaca::TaoBot

double Alpaca::TaoBot::converted_signaler_price() {
  if (this->signal.signaler.empty()) {
    return 0.00;
  }

  return current_price(this->signal.signaler) *
         this->signal.signaled_to_signaler_price_ratio;
}

#endif
