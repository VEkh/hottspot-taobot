#ifndef ALPACA__TAO_BOT_can_open_position
#define ALPACA__TAO_BOT_can_open_position

#include "has_already_stopped_profit.cpp" // has_already_stopped_profit // TODO: Decide
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "tao_bot.h"                    // Alpaca::TaoBot, fmt, order_action_t

bool Alpaca::TaoBot::can_open_position() {
  if (!this->market_availability.is_market_open(this->current_epoch)) {
    return false;
  }

  if (this->open_order_ptr) {
    return false;
  }

  if (max_account_loss_reached()) {
    return false;
  }

  // TODO: Decide
  if (has_already_stopped_profit()) {
    return false;
  }

  return true;
}

#endif
