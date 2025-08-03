#ifndef OANDA__TAO_BOT_margin_buying_power
#define OANDA__TAO_BOT_margin_buying_power

#include "tao_bot.h" // Alpaca::TaoBot

double Oanda::TaoBot::margin_buying_power() {
  return this->account_snapshot.equity * this->margin_rate.multiplier;
}

#endif
