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
      .account_currency = this->ACCOUNT_CURRENCY,
      .api_key_id = this->api_client.config.api_key_id,
      .currency = this->ACCOUNT_CURRENCY,
      .current_profit = this->open_order_ptr->profit,
      .max_profit = this->open_order_ptr->max_profit,
      .max_profit_at = this->open_order_ptr->max_profit_at,
      .min_profit = this->open_order_ptr->min_profit,
      .min_profit_at = this->open_order_ptr->min_profit_at,
      .open_order_execution_price = this->open_order_ptr->execution_price,
      .open_order_id = this->open_order_ptr->id,
      .open_order_quantity =
          quantity_multiplier * this->open_order_ptr->quantity,
      .opened_at = this->backtest.is_active ? this->current_epoch : 0,
      .stop_loss = this->exit_prices.stop_loss,
      .stop_profit = this->exit_prices.stop_profit,
      .symbol = this->symbol,
      .to_account_currency_ratio = 1.00,
  });
}

#endif
