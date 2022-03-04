#ifndef ALPACA__TAO_BOT_set_trade_direction
#define ALPACA__TAO_BOT_set_trade_direction

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::set_trade_direction() {
  const int current_losses = this->performance.loss_streaks.current;

  this->is_long_position = current_losses != 8;
}

#endif
