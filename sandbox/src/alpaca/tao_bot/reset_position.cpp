#ifndef ALPACA__TAO_BOT_reset_position
#define ALPACA__TAO_BOT_reset_position

/*
 * Alpaca::TaoBot
 * exit_prices_t
 * order_status_t
 * position_t
 */
#include "tao_bot.h"

#include "build_performance.cpp"         // build_performance
#include "should_toggle_is_trending.cpp" // should_toggle_is_trending // TODO: Decide

void Alpaca::TaoBot::reset_position() {
  if (!(this->close_order_ptr && this->open_order_ptr)) {
    return;
  }

  if (this->close_order_ptr->status != order_status_t::ORDER_FILLED ||
      this->open_order_ptr->status != order_status_t::ORDER_FILLED) {
    return;
  }

  if (this->close_order.profit < 0) {
    // TODO: Decide
    if (this->api_client.config.should_toggle_profit_timeout_seconds) {
      this->api_client.config.should_use_alt_profit_timeout_seconds =
          !this->api_client.config.should_use_alt_profit_timeout_seconds;
    }

    // TODO: Decide
    if (this->api_client.config.should_toggle_stop_loss) {
      this->api_client.config.should_use_alt_stop_loss =
          !this->api_client.config.should_use_alt_stop_loss;
    }

    // TODO: Decide
    if (this->api_client.config.should_toggle_stop_profit) {
      this->api_client.config.should_use_alt_stop_profit =
          !this->api_client.config.should_use_alt_stop_profit;
    }

    // TODO: Decide
    if (this->api_client.config.should_toggle_stop_profit_decay) {
      this->api_client.config.is_stop_profit_decayed =
          !this->api_client.config.is_stop_profit_decayed;
    }

    // TODO: Decide
    if (should_toggle_is_trending()) {
      this->is_trending = !this->is_trending;
    }
  } else {
    // TODO: Decide
    this->is_trending = false;
  }

  const position_t position = {
      .close_order = this->close_order,
      .open_order = this->open_order,
  };

  this->active_consolidation = range_t(); // TODO: Decide
  this->closed_positions.push_back(position);

  this->close_order_ptr = nullptr;
  this->exit_prices = exit_prices_t();
  this->open_order_ptr = nullptr;

  this->performance = build_performance();
}

#endif
