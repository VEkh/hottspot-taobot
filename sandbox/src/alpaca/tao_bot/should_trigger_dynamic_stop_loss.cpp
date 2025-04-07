// TODO: Decide
#ifndef ALPACA__TAO_BOT_should_trigger_dynamic_stop_loss
#define ALPACA__TAO_BOT_should_trigger_dynamic_stop_loss

#include "did_last_position_stop_profit.cpp" // did_last_position_stop_profit
#include "latest_reversal_after.cpp"         // latest_reversal_after
#include "math.h"                            // abs
#include "tao_bot.h"                         // Alpaca::TaoBot, reversal_t

bool Alpaca::TaoBot::should_trigger_dynamic_stop_loss() {
  if (!this->api_client.config.should_dynamically_stop_loss) {
    return false;
  }

  if (!this->open_order_ptr) {
    return false;
  }

  if (this->closed_positions.empty()) {
    return false;
  }

  if (!did_last_position_stop_profit()) {
    return false;
  }

  const reversal_t latest_reversal_ = latest_reversal_after(
      this->reversals, this->open_order_ptr->max_profit_at,
      this->open_order_ptr->entry_reversal.opposite_type());

  if (!latest_reversal_.at) {
    return false;
  }

  const double midway_profit =
      0.5 * (this->open_order_ptr->max_profit + this->exit_prices.stop_loss);

  if (this->open_order_ptr->profit >= midway_profit) {
    return false;
  }

  this->has_triggered_dynamic_stop_loss = true;
  return true;
}

#endif
