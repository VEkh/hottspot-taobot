#ifndef OANDA__TAO_BOT_order_duration
#define OANDA__TAO_BOT_order_duration

#include "tao_bot.h" // Oanda::TaoBot
#include <string>    // std::string

int Oanda::TaoBot::order_duration(const order_t *order_ptr,
                                  const std::string key = "open") {
  if (!order_ptr) {
    return 0;
  }

  if (key == "max_profit") {
    return this->current_epoch - order_ptr->max_profit_at;
  }

  if (key == "min_profit") {
    return this->current_epoch - order_ptr->min_profit_at;
  }

  return this->current_epoch - order_ptr->timestamp;
}

#endif
