#ifndef OANDA__TAO_BOT_set_trade_direction
#define OANDA__TAO_BOT_set_trade_direction

#include "tao_bot.h" // Oanda::TaoBot

void Oanda::TaoBot::set_trade_direction() {
  const int current_losses = this->performance.loss_streaks.current;

  this->is_long_position = !(current_losses > 0 && current_losses % 5 == 0);
}

#endif
