#ifndef ALPACA__TAO_BOT_compute_quantity
#define ALPACA__TAO_BOT_compute_quantity

#include "tao_bot.h" // Alpaca::TaoBot
#include <algorithm> // std::min
#include <math.h>    // floor

double Alpaca::TaoBot::compute_quantity() {
  const quote_t quote = this->quotes.front();
  const double margin_throttle = 1.0;

  const double max_buying_power =
      this->account_snapshot.original_margin_buying_power / margin_throttle;

  const double buying_power = max_buying_power / this->env_symbols.size();

  return floor(buying_power / (1.3 * quote.ask));
}

#endif
