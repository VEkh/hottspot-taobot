#ifndef OANDA__TAO_BOT_can_open_position
#define OANDA__TAO_BOT_can_open_position

#include "is_entry_signal_present.cpp"  // is_entry_signal_present
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "spread_limit.cpp"             // spread_limit
#include "tao_bot.h"                    // Oanda::TaoBot, fmt, order_action_t

bool Oanda::TaoBot::can_open_position() {
  if (!this->market_availability.is_market_open(this->current_epoch)) {
    return false;
  }

  if (this->open_order_ptr) {
    return false;
  }

  if (this->current_quote.spread() > spread_limit()) {
    return false;
  }

  if (max_account_loss_reached()) {
    return false;
  }

  return true;
}

#endif