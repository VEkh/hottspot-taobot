#ifndef ALPACA__TAO_BOT_compute_quantity
#define ALPACA__TAO_BOT_compute_quantity

#include "tao_bot.h"                   // Alpaca::TaoBot, order_win_result_t
#include "tradeable_symbols_count.cpp" // tradeable_symbols_count
#include <algorithm>                   // std::min
#include <math.h>                      // floor

double Alpaca::TaoBot::compute_quantity() {
  const quote_t quote = this->quotes.back();

  const double max_buying_power =
      this->account_balance.original_margin_buying_power;

  const double buying_power =
      std::min(this->account_balance.margin_buying_power,
               max_buying_power / tradeable_symbols_count());

  return floor(buying_power / (1.04 * quote.ask));
}

#endif
