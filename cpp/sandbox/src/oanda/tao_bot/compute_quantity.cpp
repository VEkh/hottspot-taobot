#ifndef OANDA__TAO_BOT_compute_quantity
#define OANDA__TAO_BOT_compute_quantity

#include "base_currency.cpp"           // base_currency
#include "convert_price.cpp"           // convert_price
#include "tao_bot.h"                   // Alpaca::TaoBot
#include "tradeable_symbols_count.cpp" // tradeable_symbols_count
#include <algorithm>                   // std::min
#include <math.h>                      // floor

int Oanda::TaoBot::compute_quantity() {
  const quote_t quote = this->quotes.back();
  const double dollars_per_unit = convert_price(1.0, base_currency(), "USD");

  const double max_buying_power =
      this->account_snapshot.equity * this->account_snapshot.margin_multiplier;

  const double buying_power = max_buying_power / tradeable_symbols_count();

  return floor(buying_power / dollars_per_unit);
}

#endif
