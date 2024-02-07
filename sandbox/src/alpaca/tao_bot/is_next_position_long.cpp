#ifndef ALPACA__TAO_BOT_is_next_position_long
#define ALPACA__TAO_BOT_is_next_position_long

#include "current_mid.cpp"            // current_mid
#include "does_position_exist.cpp"    // does_position_exist
#include "is_first_position_long.cpp" // is_first_position_long
#include "lib/utils/boolean.cpp"      // ::utils::boolean
#include "tao_bot.h"                  // Alpaca::TaoBot, order_action_t

// TODO: Decide
#include "candles_range.cpp"                       // candles_range
#include "is_consolidation_next_position_long.cpp" // is_consolidation_next_position_long
#include "is_nearest_reversal_low.cpp"             // is_nearest_reversal_low
#include "is_reversing_loss.cpp"                   // is_reversing_loss
#include "reversal_imbalance.cpp"                  // reversal_imbalance

bool Alpaca::TaoBot::is_next_position_long() {
  if (this->candle_predictor.should_predict(does_position_exist())) {
    if (this->closed_positions.empty()) {
      return this->candle_predictor.is_next_position_long();
    }

    if (!this->candle_predictor.config.rollover_positions) {
      return this->candle_predictor.is_next_position_long();
    }
  }

  // TODO: Decide
  if (this->api_client.config.should_reverse_losses && is_reversing_loss()) {
    const position_t last_position = this->closed_positions.back();

    return last_position.close_order.action == order_action_t::BUY;
  }

  // TODO: Decide
  if (this->api_client.config.should_await_reversal_indicator) {
    if (this->is_trending) {
      return !is_nearest_reversal_low();
    }

    return is_nearest_reversal_low();
  }

  // TODO: Decide
  if (this->api_client.config.should_await_consolidation_indicator) {
    return is_consolidation_next_position_long(
        this->active_consolidation_duration_minutes);
  }

  if (this->closed_positions.empty()) {
    return is_first_position_long();
  }

  const position_t last_position = this->closed_positions.back();

  return last_position.close_order.action == order_action_t::BUY;
};

#endif
