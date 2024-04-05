#ifndef ALPACA__TAO_BOT_is_next_position_long
#define ALPACA__TAO_BOT_is_next_position_long

#include "current_mid.cpp"            // current_mid
#include "does_position_exist.cpp"    // does_position_exist
#include "is_first_position_long.cpp" // is_first_position_long
#include "lib/utils/boolean.cpp"      // ::utils::boolean
#include "tao_bot.h" // Alpaca::TaoBot, order_action_t reversal_type_t

bool Alpaca::TaoBot::is_next_position_long() {
  if (this->api_client.config.should_await_reversal_indicator) {
    return this->entry_reversal.type == reversal_type_t::REVERSAL_LOW;
  }

  if (this->closed_positions.empty()) {
    return is_first_position_long();
  }

  const position_t last_position = this->closed_positions.back();

  return last_position.close_order.action == order_action_t::BUY;
};

#endif
