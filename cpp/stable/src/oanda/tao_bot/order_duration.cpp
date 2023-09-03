#ifndef OANDA__TAO_BOT_order_duration
#define OANDA__TAO_BOT_order_duration

#include "tao_bot.h" // Oanda::TaoBot
#include <ctime>     // std::time, std::time_t

int Oanda::TaoBot::order_duration(const order_t *order_ptr) {
  if (!order_ptr) {
    return 0;
  }

  return std::time(nullptr) - order_ptr->timestamp;
}

#endif
