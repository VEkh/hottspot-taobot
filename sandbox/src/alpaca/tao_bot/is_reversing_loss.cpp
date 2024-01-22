// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_reversing_loss
#define ALPACA__TAO_BOT_is_reversing_loss

#include "tao_bot.h" // Alpaca::TaoBot

bool Alpaca::TaoBot::is_reversing_loss() {
  if (!this->api_client.config.should_await_consolidation_indicator) {
    return false;
  }

  return false;

  if (this->closed_positions.empty()) {
    return false;
  }

  position_t last_position = this->closed_positions.back();

  if (last_position.open_order.is_loss_reversal) {
    return false;
  }

  return last_position.close_order.profit < 0;
}

#endif
