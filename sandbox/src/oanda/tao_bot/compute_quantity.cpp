#ifndef OANDA__TAO_BOT_compute_quantity
#define OANDA__TAO_BOT_compute_quantity

#include "base_currency.cpp"       // base_currency
#include "convert_price.cpp"       // convert_price
#include "margin_buying_power.cpp" // margin_buying_power
#include "tao_bot.h"               // Alpaca::TaoBot
#include "update_margin_rate.cpp"  // update_margin_rate
#include <math.h>                  // floor

int Oanda::TaoBot::compute_quantity() {
  const double dollars_per_unit = convert_price(1.0, base_currency(), "USD");

  update_margin_rate();

  const double buying_power = margin_buying_power() / this->env_symbols.size();

  return floor(buying_power / dollars_per_unit);
}

#endif
