#ifndef OANDA__TAO_BOT_is_next_position_long
#define OANDA__TAO_BOT_is_next_position_long

#include "lib/utils/boolean.cpp" // ::utils::boolean
#include "order_win_result.cpp"  // order_win_result
#include "tao_bot.h" // Oanda::TaoBot, order_action_t, order_win_result_t

bool Oanda::TaoBot::is_next_position_long() {
  if (!this->closed_positions.size()) {
    return ::utils::boolean::flip_coin();
  }

  const position_t last_position = this->closed_positions.back();

  if (order_win_result(last_position) == order_win_result_t::WIN) {
    return last_position.open_order.action == order_action_t::BUY;
  }

  return last_position.close_order.action == order_action_t::BUY;
};

#endif
