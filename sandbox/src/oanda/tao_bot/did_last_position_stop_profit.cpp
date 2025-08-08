#ifndef OANDA__TAO_BOT_did_last_position_stop_profit
#define OANDA__TAO_BOT_did_last_position_stop_profit

#include "tao_bot.h" // Oanda::TaoBot

bool Oanda::TaoBot::did_last_position_stop_profit() {
  if (this->closed_positions.empty()) {
    return false;
  }

  const position_t last_position = this->closed_positions.back();

  return (bool)last_position.close_order.stop_profit_reversal.at;
}

#endif
