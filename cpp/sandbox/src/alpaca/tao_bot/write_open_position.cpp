#ifndef ALPACA__TAO_BOT_write_open_position
#define ALPACA__TAO_BOT_write_open_position

#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, order_status_t

void Alpaca::TaoBot::write_open_position() {
  if (!this->open_order_ptr) {
    return;
  }

  if (this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  const int quantity_multiplier =
      this->open_order_ptr->action == order_action_t::BUY ? 1 : -1;

  this->db_position.open({
      .api_key_id = this->api_client.config.api_key_id,
      .current_profit = this->open_order_ptr->profit,
      .max_profit = this->open_order_ptr->max_profit,
      .max_profit_at = this->open_order_ptr->max_profit_timestamp,
      .open_order_execution_mid = this->open_order_ptr->execution_price,
      .open_order_id = this->open_order_ptr->id,
      .open_order_quantity =
          quantity_multiplier * this->open_order_ptr->quantity,
      .stop_loss = this->exit_prices.max_loss,
      .stop_profit = this->exit_prices.min_profit,
      .symbol = this->symbol,
  });
}

#endif
