#ifndef ALPACA__TAO_BOT_await_next_poll
#define ALPACA__TAO_BOT_await_next_poll

#include "math.h"                   // abs
#include "max_loss_ratio.cpp"       // max_loss_ratio
#include "open_position_profit.cpp" // open_position_profit
#include "tao_bot.h"                // Alpaca::TaoBot

void Alpaca::TaoBot::await_next_poll() {
  double await_time = 5e5;

  if (this->open_order_ptr &&
      this->open_order_ptr->status == order_status_t::ORDER_FILLED) {
    const double profit_ratio =
        this->open_order_ptr->profit / this->open_order_ptr->execution_price;

    if ((abs(profit_ratio / max_loss_ratio(this->open_order_ptr))) >= 0.7) {
      await_time = profit_ratio > 0 ? 1e6 : 5e4;
    }
  }

  usleep(await_time);
}

#endif
