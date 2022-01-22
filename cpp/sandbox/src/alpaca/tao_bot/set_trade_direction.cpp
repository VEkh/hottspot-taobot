#ifndef ALPACA__TAO_BOT_set_trade_direction
#define ALPACA__TAO_BOT_set_trade_direction

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::set_trade_direction() {
  const int loss_streak = this->performance.loss_streaks.current;

  if (!loss_streak) {
    this->is_long_position = true;
  }

  if (loss_streak < 4) {
    this->is_long_position = (bool)!this->is_long_position;
  }

  if (loss_streak < 8) {
    this->is_long_position = true;
  }

  this->is_long_position = (bool)!this->is_long_position;
}

#endif
