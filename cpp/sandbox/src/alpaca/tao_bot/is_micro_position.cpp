#ifndef ALPACA__TAO_BOT_is_micro_position
#define ALPACA__TAO_BOT_is_micro_position

#include "order_win_result.cpp" // order_win_result
#include "tao_bot.h"            // Alpaca::TaoBot, position_t
#include <math.h>               // abs

bool Alpaca::TaoBot::is_micro_position() {
  if (this->closed_positions.empty()) {
    return true;
  }

  const position_t last_position = this->closed_positions.back();

  if (order_win_result(last_position) != order_win_result_t::WIN) {
    return true;
  }

  return !is_micro_position(last_position);
}

bool Alpaca::TaoBot::is_micro_position(const position_t &position) {
  return abs(position.close_order.quantity) == this->MICRO_QUANTITY;
}

#endif
