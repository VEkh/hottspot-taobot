#ifndef ALPACA__TAO_BOT_build_exit_prices
#define ALPACA__TAO_BOT_build_exit_prices

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // abs

Alpaca::TaoBot::exit_prices_t Alpaca::TaoBot::build_exit_prices() {
  const double static_one_sec_variance = this->one_sec_variance_avgs.running;

  const int max_loss_coefficient = -62.5;
  const double trailing_stop_profit_ratio = 1 / 1.1;

  const double max_loss = max_loss_coefficient * static_one_sec_variance;
  double stop_profit = abs(2.5 * max_loss);

  if (this->api_client.config.is_live) {
    const double computed_stop_profit =
        this->quoter.db_quote.get_stop_profit(this->symbol);

    stop_profit = computed_stop_profit ? computed_stop_profit : stop_profit;
  }

  const double min_profit = stop_profit / trailing_stop_profit_ratio;

  const double trailing_stop_profit =
      this->open_order_ptr->max_profit * trailing_stop_profit_ratio;

  exit_prices_t out = {
      .max_loss = max_loss,
      .min_profit = min_profit,
      .trailing_stop_profit = trailing_stop_profit,
  };

  return out;
}

#endif
