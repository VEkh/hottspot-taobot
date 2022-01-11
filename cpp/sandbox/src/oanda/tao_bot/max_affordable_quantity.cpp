#ifndef OANDA__TAO_BOT_max_affordable_quantity
#define OANDA__TAO_BOT_max_affordable_quantity

#include "base_currency.cpp" // base_currency
#include "convert_price.cpp" // convert_price
#include "current_price.cpp" // current_price
#include "tao_bot.h"         // Oanda::TaoBot

int Oanda::TaoBot::max_affordable_quantity() {
  const double converted_price =
      convert_price(current_price(), base_currency(), "USD");

  return this->account_balance.margin_buying_power / converted_price;
}

#endif
