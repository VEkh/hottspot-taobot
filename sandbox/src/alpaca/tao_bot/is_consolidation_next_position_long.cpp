// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_consolidation_next_position_long
#define ALPACA__TAO_BOT_is_consolidation_next_position_long

#include "candles_range.cpp"                  // candles_range
#include "current_mid.cpp"                    // current_mid
#include "is_closer_to_consolidation_low.cpp" // is_closer_to_consolidation_low
#include "is_reversing_loss.cpp"              // is_reversing_loss
#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, range_t

bool Alpaca::TaoBot::is_consolidation_next_position_long(const int range_n) {
  if (is_reversing_loss()) {
    const position_t last_position = this->closed_positions.back();
    return last_position.open_order.action == order_action_t::SELL;
  }

  const double mid = current_mid();
  const int half_candles_n = range_n / 2;

  range_t range = candles_range(range_n);

  if (mid > range.high) {
    return true;
  }

  if (mid < range.low) {
    return false;
  }

  return is_closer_to_consolidation_low(range_n);
}

#endif
