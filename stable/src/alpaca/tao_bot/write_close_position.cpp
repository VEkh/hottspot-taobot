#ifndef ALPACA__TAO_BOT_write_close_position
#define ALPACA__TAO_BOT_write_close_position

#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, order_status_t
#include <algorithm> // std::max

void Alpaca::TaoBot::write_close_position() {
  if (!this->close_order_ptr) {
    return;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  const double max_profit =
      std::max(this->close_order_ptr->profit, this->open_order_ptr->max_profit);

  const double max_profit_at = max_profit == this->close_order_ptr->profit
                                   ? this->close_order_ptr->timestamp
                                   : this->open_order_ptr->max_profit_timestamp;

  const int quantity_multiplier =
      this->close_order_ptr->action == order_action_t::BUY ? 1 : -1;

  this->db_position.close({
      .api_key_id = this->api_client.config.api_key_id,
      .close_order_execution_mid = this->close_order_ptr->execution_price,
      .close_order_id = this->close_order_ptr->id,
      .close_order_quantity =
          quantity_multiplier * this->close_order_ptr->quantity,
      .closed_at = this->close_order_ptr->timestamp,
      .current_profit = this->close_order_ptr->profit,
      .max_profit = max_profit,
      .max_profit_at = max_profit_at,
      .open_order_id = this->open_order_ptr->id,
      .stop_loss = this->exit_prices.max_loss,
      .stop_profit = this->exit_prices.min_profit,
  });
}

#endif