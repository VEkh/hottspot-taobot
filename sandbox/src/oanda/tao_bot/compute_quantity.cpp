#ifndef OANDA__TAO_BOT_compute_quantity
#define OANDA__TAO_BOT_compute_quantity

#include "convert_price.cpp"       // convert_price
#include "margin_buying_power.cpp" // margin_buying_power
#include "tao_bot.h" // Oanda::TaoBot, order_action_t // TODO: Decide
#include "update_margin_rate.cpp" // update_margin_rate
#include <math.h>                 // abs // TODO: Decide, floor

// TODO: Decide
#include "build_exit_prices.cpp"            // build_exit_prices
#include "is_next_position_long.cpp"        // is_next_position_long
#include "normalized_margin_multiplier.cpp" // normalized_margin_multiplier
#include <algorithm>                        // std::min

long int Oanda::TaoBot::compute_quantity() {
  const double dollars_per_unit = convert_price({
      .debug = true,
      .from = this->currency.base,
      .price = 1.0,
      .to = "USD",
  });

  update_margin_rate();

  const double full_buying_power =
      margin_buying_power() / this->env_symbols.size();

  // TODO: Decide
  // normalization v0.4
  if (this->api_client.config.normalized_account_loss_ratio) {
    const double normalized_account_loss_ratio =
        this->api_client.config.normalized_account_loss_ratio;

    const order_action_t action =
        is_next_position_long() ? order_action_t::BUY : order_action_t::SELL;

    const exit_prices_t exit_prices_ = build_exit_prices({
        .action = action,
        .day_candle = this->day_candle,
        .entry_reversal = this->entry_reversal,
        .execution_price = this->current_quote.mid(),
    });

    const double position_stop_loss_dollars =
        abs(exit_prices_.stop_loss) * dollars_per_unit;

    const double normalized_loss_buying_power =
        abs(normalized_account_loss_ratio) * this->account_snapshot.equity;

    const double buying_power =
        std::min(normalized_loss_buying_power, full_buying_power);

    return floor(normalized_loss_buying_power / position_stop_loss_dollars);
  }

  // TODO: Decide
  const double buying_power =
      full_buying_power * normalized_margin_multiplier();

  return floor(buying_power / dollars_per_unit);
}

#endif
