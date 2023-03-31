#ifndef ALPACA__TAO_BOT_write_position
#define ALPACA__TAO_BOT_write_position

/*
 * Alpaca::TaoBot
 * exit_prices_t
 * order_action_t
 * position_t
 */
#include "tao_bot.h"

#include "build_performance.cpp" // build_performance
#include "write_performance.cpp" // write_performance
#include "write_position.cpp"    // write_position

void Alpaca::TaoBot::write_position(const position_t &position,
                                    const exit_prices_t &exit_prices_) {
  const int close_quantity_multiplier =
      position.close_order.action == order_action_t::BUY ? 1 : -1;
  const int open_quantity_multiplier =
      position.open_order.action == order_action_t::BUY ? 1 : -1;

  this->db_position.insert({
      .api_key_id = this->api_client.config.api_key_id,
      .close_order_execution_mid = position.close_order.execution_price,
      .close_order_id = position.close_order.id,
      .close_order_quantity =
          close_quantity_multiplier * position.close_order.quantity,
      .closed_at = position.close_order.timestamp,
      .max_profit = position.open_order.max_profit,
      .max_profit_at = position.open_order.max_profit_timestamp,
      .open_order_execution_mid = position.open_order.execution_price,
      .open_order_id = position.open_order.id,
      .open_order_quantity =
          open_quantity_multiplier * position.open_order.quantity,
      .opened_at = position.open_order.timestamp,
      .stop_loss = exit_prices_.max_loss,
      .stop_profit = exit_prices_.min_profit,
      .symbol = this->symbol,
  });
}

#endif
