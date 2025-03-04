#ifndef OANDA__TAO_BOT_write_open_position
#define OANDA__TAO_BOT_write_open_position

#include "tao_bot.h" // Oanda::TaoBot, order_action_t, order_status_t
#include <string>    // std::to_string

void Oanda::TaoBot::write_open_position() {
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
      .api_key_id = this->api_client.config.account_id,
      .currency = this->currency.quote,
      .current_profit = this->open_order_ptr->profit,
      .max_profit = this->open_order_ptr->max_profit,
      .max_profit_at = this->open_order_ptr->max_profit_at,
      .min_profit = this->open_order_ptr->min_profit,
      .min_profit_at = this->open_order_ptr->min_profit_at,
      .open_order_execution_price = this->open_order_ptr->execution_price,
      .open_order_id = std::to_string(this->open_order_ptr->id),
      .open_order_quantity =
          (double)(quantity_multiplier * this->open_order_ptr->quantity),
      .opened_at = this->backtest.is_active ? this->current_epoch : 0,
      .stop_loss = this->exit_prices.stop_loss,
      .stop_profit = this->exit_prices.stop_profit,
      .symbol = this->symbol,
      .to_account_currency_ratio =
          this->open_order_ptr->to_account_currency_ratio,
  });
}

#endif
