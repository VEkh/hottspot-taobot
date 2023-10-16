#ifndef ALPACA__TAO_BOT_is_next_position_long
#define ALPACA__TAO_BOT_is_next_position_long

#include "current_mid.cpp"            // current_mid
#include "is_first_position_long.cpp" // is_first_position_long
#include "lib/utils/boolean.cpp"      // ::utils::boolean
#include "tao_bot.h"                  // Alpaca::TaoBot, order_action_t

bool Alpaca::TaoBot::is_next_position_long() {
  const std::string api_key = this->api_client.config.api_key;

  if (this->five_min_predict.should_predict()) {
    return this->five_min_predict.is_next_position_long({
        .current_mid = current_mid(),
        .range_buffer = this->avg_one_sec_variances.running * 60,
    });
  } else {
    if (this->closed_positions.empty()) {
      return is_first_position_long();
    }

    const position_t last_position = this->closed_positions.back();

    return last_position.close_order.action == order_action_t::BUY;
  }

  return true;
};

#endif
