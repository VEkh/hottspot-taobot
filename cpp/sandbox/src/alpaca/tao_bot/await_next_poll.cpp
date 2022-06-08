#ifndef ALPACA__TAO_BOT_await_next_poll
#define ALPACA__TAO_BOT_await_next_poll

#include "math.h"                   // abs
#include "max_loss_ratio.cpp"       // max_loss_ratio
#include "open_position_profit.cpp" // open_position_profit
#include "tao_bot.h"                // Alpaca::TaoBot

void Alpaca::TaoBot::await_next_poll() {
  double await_time = 5e5;

  if (this->open_order_ptr &&
      this->open_order_ptr->status == order_status_t::ORDER_FILLED &&
      this->exit_prices.max_loss) {
    const double profit_ratio =
        this->open_order_ptr->profit / this->exit_prices.max_loss;

    if (abs(profit_ratio) >= 0.7 && this->open_order_ptr->profit > 0) {
      await_time = 1e6;
    }
  }

  usleep(await_time);
}

#endif
