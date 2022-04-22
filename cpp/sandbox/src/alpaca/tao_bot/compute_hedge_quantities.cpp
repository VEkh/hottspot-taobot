#ifndef ALPACA__TAO_BOT_compute_hedge_quantities
#define ALPACA__TAO_BOT_compute_hedge_quantities

#include "hedge_symbol.cpp"            // hedge_symbol
#include "tao_bot.h"                   // Alpaca::TaoBot
#include "tradeable_symbols_count.cpp" // tradeable_symbols_count
#include <algorithm>                   // std::min
#include <math.h>                      // floor
#include <utility>                     // std::pair

std::pair<double, double> Alpaca::TaoBot::compute_hedge_quantities() {
  const quote_t base_quote = this->quotes.back();
  const quote_t hedge_quote = this->hedge_quotes.back();

  const price_movement_t base_price_movement =
      this->price_movements[this->symbol];
  const price_movement_t hedge_price_movement =
      this->price_movements[hedge_symbol()];

  const double base_one_sec_variance =
      base_price_movement.short_term_three_minute_one_second_variance.average
          ? base_price_movement.short_term_three_minute_one_second_variance
                .average
          : base_price_movement.three_minute_one_second_variance.average;

  const double hedge_one_sec_variance =
      hedge_price_movement.short_term_three_minute_one_second_variance.average
          ? hedge_price_movement.short_term_three_minute_one_second_variance
                .average
          : hedge_price_movement.three_minute_one_second_variance.average;

  const double normalization_factor =
      (hedge_quote.ask / base_quote.ask) *
      this->price_movements[this->symbol].ratio_from_hedge.average;

  const double hedge_quantity = 1;
  const double base_quantity_ = hedge_quantity * normalization_factor;

  const double max_buying_power = 0.95 * this->account_balance.balance *
                                  this->account_balance.margin_multiplier;

  const double buying_power =
      std::min(this->account_balance.margin_buying_power,
               max_buying_power / tradeable_symbols_count());

  const double adjusted_hedge_quantity =
      floor(buying_power /
            ((normalization_factor * base_quote.ask) + hedge_quote.ask));

  const double adjusted_base_quantity =
      adjusted_hedge_quantity * normalization_factor;

  return {adjusted_base_quantity, adjusted_hedge_quantity};
}

#endif
