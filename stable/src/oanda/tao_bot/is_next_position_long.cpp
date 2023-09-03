#ifndef OANDA__TAO_BOT_is_next_position_long
#define OANDA__TAO_BOT_is_next_position_long

#include "is_first_position_long.cpp" // is_first_position_long
#include "lib/utils/boolean.cpp"      // ::utils::boolean
#include "tao_bot.h"                  // Oanda::TaoBot, order_action_t

bool Oanda::TaoBot::is_next_position_long() {
  if (!this->closed_positions.size()) {
    return is_first_position_long();
  }

  const position_t last_position = this->closed_positions.back();

  return last_position.close_order.action == order_action_t::BUY;
};
#endif
