// TODO: Decide
#ifndef OANDA__TAO_BOT_has_just_stopped_double_reverse
#define OANDA__TAO_BOT_has_just_stopped_double_reverse

#include "tao_bot.h" // Oanda::TaoBot, position_t

bool Oanda::TaoBot::has_just_stopped_double_reverse() {
  if (!this->api_client.config.should_avoid_double_reverse) {
    return false;
  }

  if (this->closed_positions.size() < 2) {
    return false;
  }

  const position_t penultimate_position =
      this->closed_positions.at(this->closed_positions.size() - 2);

  if (!penultimate_position.close_order.stop_profit_reversal.at) {
    return false;
  }

  return true;
}

#endif
