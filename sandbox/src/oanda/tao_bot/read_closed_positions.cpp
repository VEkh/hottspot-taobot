#ifndef OANDA__TAO_BOT_read_closed_positions
#define OANDA__TAO_BOT_read_closed_positions

#include "tao_bot.h" // Oanda::TaoBot, db_position_t, order_time_in_force_t
#include <list>      // std::list
#include <math.h>    // abs
#include <string>    // std::stoi

void Oanda::TaoBot::read_closed_positions() {
  std::list<db_position_t> day_positions =
      this->db_position.get_closed_positions({
          .api_key_id = this->api_client.config.account_id,
          .debug = this->api_client.config.debug_sql,
          .market_open_epoch = this->market_availability.market_epochs.open,
          .symbol = this->symbol,
      });

  for (const db_position_t db_position : day_positions) {
    order_t close_order_ = {
        .account_currency = db_position.account_currency,
        .action = db_position.close_order_quantity > 0 ? order_action_t::BUY
                                                       : order_action_t::SELL,
        .currency = db_position.currency,
        .execution_price = db_position.close_order_execution_mid,
        .id = std::stoi(db_position.close_order_id),
        .max_position_profit =
            db_position.max_profit * abs(db_position.close_order_quantity),
        .max_profit = db_position.max_profit,
        .max_profit_at = db_position.max_profit_at,
        .min_profit = db_position.min_profit,
        .min_profit_at = db_position.min_profit_at,
        .profit = db_position.current_profit,
        .quantity = (int)abs(db_position.close_order_quantity),
        .status = order_status_t::ORDER_FILLED,
        .stop_loss = db_position.stop_loss,
        .stop_profit = db_position.stop_profit,
        .symbol = db_position.symbol,
        .time_in_force = order_time_in_force_t::FOK,
        .timestamp = db_position.closed_at,
        .to_account_currency_ratio = db_position.to_account_currency_ratio,
        .type = order_type_t::MARKET,
    };

    order_t open_order_ = {
        .account_currency = db_position.account_currency,
        .action = db_position.open_order_quantity > 0 ? order_action_t::BUY
                                                      : order_action_t::SELL,
        .currency = db_position.currency,
        .execution_price = db_position.open_order_execution_mid,
        .id = std::stoi(db_position.open_order_id),
        .max_position_profit =
            db_position.max_profit * abs(db_position.open_order_quantity),
        .max_profit = db_position.max_profit,
        .max_profit_at = db_position.max_profit_at,
        .min_profit = db_position.min_profit,
        .min_profit_at = db_position.min_profit_at,
        .profit = db_position.current_profit,
        .quantity = (int)abs(db_position.open_order_quantity),
        .status = order_status_t::ORDER_FILLED,
        .stop_loss = db_position.stop_loss,
        .stop_profit = db_position.stop_profit,
        .symbol = db_position.symbol,
        .time_in_force = order_time_in_force_t::FOK,
        .timestamp = db_position.opened_at,
        .to_account_currency_ratio = db_position.to_account_currency_ratio,
        .type = order_type_t::MARKET,
    };

    this->closed_positions.push_back({
        .close_order = close_order_,
        .open_order = open_order_,
    });
  }
}

#endif
