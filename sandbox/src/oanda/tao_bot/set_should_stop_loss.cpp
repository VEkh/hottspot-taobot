// TODO: Decide
#ifndef OANDA__TAO_BOT_set_should_stop_loss
#define OANDA__TAO_BOT_set_should_stop_loss

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::set_should_stop_loss() {
  if (!this->open_order_ptr) {
    return;
  }

  const double current_range_open_percent =
      this->day_candle.range_open_percent();

  const double open_order_range_open_percent =
      this->open_order_ptr->day_candle.range_open_percent();

  const double ratio =
      current_range_open_percent / open_order_range_open_percent;

  this->should_stop_loss = ratio >= 3.0;
}

#endif
