#ifndef ALPACA__TAO_BOT_is_next_position_long
#define ALPACA__TAO_BOT_is_next_position_long

#include "is_first_position_long.cpp" // is_first_position_long
#include "lib/utils/boolean.cpp"      // ::utils::boolean
#include "tao_bot.h"                  // Alpaca::TaoBot, order_action_t

#include <string> // std::string

bool Alpaca::TaoBot::is_next_position_long() {
  const std::string api_key = this->api_client.config.api_key;

  if (api_key == "backtest-ml-10" &&
      this->ten_min_predict.should_predict(api_key)) {
    return this->ten_min_predict.predict_action() == order_action_t::BUY;
  } else if (this->five_min_predict.should_predict(api_key)) {
    return this->five_min_predict.predict_action() == order_action_t::BUY;
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
