#ifndef OANDA__TAO_BOT_stop_loss_reversals_name
#define OANDA__TAO_BOT_stop_loss_reversals_name

#include "tao_bot.h" // Oanda::TaoBot
#include <string>    // std::string

std::string Oanda::TaoBot::stop_loss_reversals_name() {
  const std::string config = this->api_client.config.stop_loss_reversals_name;

  return config;

  if (this->closed_positions.empty()) {
    return config;
  }

  const position_t last_position = this->closed_positions.back();

  if (last_position.close_order.stop_profit_reversal.mid) {
    // return "secondary";
    return "primary";
  }

  return config;
}

#endif
