#ifndef ALPACA__TAO_BOT_set_open_signal
#define ALPACA__TAO_BOT_set_open_signal

/*
 * Alpaca::TaoBot
 * order_action_t
 * order_status_t
 */
#include "tao_bot.h"

#include "current_price.cpp"             // current_price
#include "price_movement_pair_ratio.cpp" // price_movement_pair_ratio
#include <ctime>                         // std::time

void Alpaca::TaoBot::set_open_signal() {
  if (this->open_order_ptr &&
      this->open_order_ptr->status == order_status_t::ORDER_FILLED) {
    return;
  }

  const price_movement_average_t ratio_to_pair =
      this->price_movements[this->symbol].ratio_to_pair;

  if (!ratio_to_pair.average) {
    return;
  }

  int signal_expiration = 30 * 60;
  const int now = std::time(nullptr);

  if (!this->open_signal.signaler.empty()) {
    const double converted_signaler_price_ =
        converted_signaler_price(this->open_signal);
    const double signaled_price = current_price(this->open_signal.signaled);

    if (this->open_signal.signaler_trend_direction == order_action_t::BUY &&
        converted_signaler_price_ < signaled_price) {
      this->open_signal.signaler_trend_direction = order_action_t::SELL;
      this->open_signal.signaler_trend_started_at = now;
    } else if (this->open_signal.signaler_trend_direction ==
                   order_action_t::SELL &&
               converted_signaler_price_ > signaled_price) {
      this->open_signal.signaler_trend_direction = order_action_t::BUY;
      this->open_signal.signaler_trend_started_at = now;
    }

    if ((this->open_signal.created_at - now) < signal_expiration) {
      return;
    }
  }

  const std::string hedge_symbol_ = "";

  if (ratio_to_pair.average >= 1) {
    const double ratio =
        current_price(hedge_symbol_) / current_price(this->symbol);

    this->open_signal = {
        .created_at = now,
        .signaled = hedge_symbol_,
        .signaled_to_signaler_price_ratio = ratio,
        .signaler = this->symbol,
        .signaler_trend_direction = order_action_t::BUY,
        .signaler_trend_started_at = now,
    };
  } else {
    const double ratio =
        current_price(this->symbol) / current_price(hedge_symbol_);

    this->open_signal = {
        .created_at = now,
        .signaled = this->symbol,
        .signaled_to_signaler_price_ratio = ratio,
        .signaler = hedge_symbol_,
        .signaler_trend_direction = order_action_t::BUY,
        .signaler_trend_started_at = now,
    };
  }
}

#endif
