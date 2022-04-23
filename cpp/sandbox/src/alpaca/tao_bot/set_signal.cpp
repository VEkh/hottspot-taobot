#ifndef ALPACA__TAO_BOT_set_signal
#define ALPACA__TAO_BOT_set_signal

#include "current_price.cpp"             // current_price
#include "hedge_symbol.cpp"              // hedge_symbol
#include "price_movement_pair_ratio.cpp" // price_movement_pair_ratio
#include "tao_bot.h"                     // Alpaca::TaoBot, order_status_t

void Alpaca::TaoBot::set_signal() {
  if (this->open_order_ptr &&
      this->open_order_ptr->status == order_status_t::ORDER_FILLED) {
    return;
  }

  const price_movement_average_t ratio_to_pair =
      this->price_movements[this->symbol].ratio_to_pair;

  if (!ratio_to_pair.average) {
    return;
  }

  const std::string hedge_symbol_ = hedge_symbol();

  if (ratio_to_pair.average >= 1) {
    const double ratio =
        current_price(hedge_symbol_) / current_price(this->symbol);

    this->signal = {
        .signaled = hedge_symbol_,
        .signaled_to_signaler_price_ratio = ratio,
        .signaler = this->symbol,
    };
  } else {
    const double ratio =
        current_price(this->symbol) / current_price(hedge_symbol_);

    this->signal = {
        .signaled = this->symbol,
        .signaled_to_signaler_price_ratio = ratio,
        .signaler = hedge_symbol_,
    };
  }
}

#endif
