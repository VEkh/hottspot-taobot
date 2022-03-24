#ifndef ALPACA__TAO_BOT_compute_hedge_quantity
#define ALPACA__TAO_BOT_compute_hedge_quantity

#include "tao_bot.h"                   // Alpaca::TaoBot
#include "tradeable_symbols_count.cpp" // tradeable_symbols_count
#include <algorithm>                   // std::min
#include <math.h>                      // floor

double Alpaca::TaoBot::compute_hedge_quantity() {
  const account_balance_t limiting_account_balance =
      this->account_balance.balance <= this->hedge_account_balance.balance
          ? this->account_balance
          : this->hedge_account_balance;

  const double max_buying_power = 0.95 * limiting_account_balance.balance *
                                  limiting_account_balance.margin_multiplier;

  const double buying_power =
      std::min(limiting_account_balance.margin_buying_power,
               max_buying_power / tradeable_symbols_count());

  const double current_ask = this->quotes.back().ask;

  return floor(buying_power / current_ask);
}

#endif
