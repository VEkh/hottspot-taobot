#ifndef ALPACA__TAO_BOT_set_stop_loss_signal
#define ALPACA__TAO_BOT_set_stop_loss_signal

/*
 * Alpaca::TaoBot
 * order_action_t
 * order_status_t
 */
#include "tao_bot.h"

#include "current_price.cpp"             // current_price
#include "hedge_symbol.cpp"              // hedge_symbol
#include "price_movement_pair_ratio.cpp" // price_movement_pair_ratio
#include <ctime>                         // std::time

void Alpaca::TaoBot::set_stop_loss_signal() {
  if (!(this->open_order_ptr &&
        this->open_order_ptr->status == order_status_t::ORDER_FILLED)) {
    return;
  }

  const int now = std::time(nullptr);

  if (this->stop_loss_signal.signaled.empty()) {
    const double ratio = current_price(this->open_signal.signaled) /
                         current_price(this->open_signal.signaler);

    this->stop_loss_signal = {
        .created_at = now,
        .signaled = this->open_signal.signaled,
        .signaled_to_signaler_price_ratio = ratio,
        .signaler = this->open_signal.signaler,
        .signaler_trend_direction = this->open_signal.signaler_trend_direction,
        .signaler_trend_started_at = now,
    };

    return;
  }

  const double converted_signaler_price_ =
      converted_signaler_price(this->stop_loss_signal);
  const double signaled_price = current_price(this->stop_loss_signal.signaled);

  if (this->stop_loss_signal.signaler_trend_direction == order_action_t::BUY &&
      converted_signaler_price_ < signaled_price) {
    this->stop_loss_signal.signaler_trend_direction = order_action_t::SELL;
    this->stop_loss_signal.signaler_trend_started_at = now;
  } else if (this->stop_loss_signal.signaler_trend_direction ==
                 order_action_t::SELL &&
             converted_signaler_price_ > signaled_price) {
    this->stop_loss_signal.signaler_trend_direction = order_action_t::BUY;
    this->stop_loss_signal.signaler_trend_started_at = now;
  }
}

#endif
