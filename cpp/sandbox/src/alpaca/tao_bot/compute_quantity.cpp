#ifndef ALPACA__TAO_BOT_compute_quantity
#define ALPACA__TAO_BOT_compute_quantity

#include "tao_bot.h"                   // Alpaca::TaoBot
#include "tradeable_symbols_count.cpp" // tradeable_symbols_count
#include <algorithm>                   // std::min
#include <math.h>                      // floor

double Alpaca::TaoBot::compute_quantity(const std::string &symbol_) {
  const quote_t quote = this->quotes[symbol_].back();

  const double max_buying_power = 0.95 * this->account_balance.balance *
                                  this->account_balance.margin_multiplier;

  const double buying_power =
      std::min(this->account_balance.margin_buying_power,
               max_buying_power / tradeable_symbols_count());

  return floor(buying_power / (1.04 * quote.ask));
}

#endif
