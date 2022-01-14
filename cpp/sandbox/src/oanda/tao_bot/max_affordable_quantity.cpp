#ifndef OANDA__TAO_BOT_max_affordable_quantity
#define OANDA__TAO_BOT_max_affordable_quantity

#include "base_currency.cpp" // base_currency
#include "convert_price.cpp" // convert_price
#include "tao_bot.h"         // Oanda::TaoBot

int Oanda::TaoBot::max_affordable_quantity() {
  const double dollars_per_unit = convert_price(1.0, base_currency(), "USD");

  return this->account_balance.margin_buying_power / dollars_per_unit;
}

#endif
