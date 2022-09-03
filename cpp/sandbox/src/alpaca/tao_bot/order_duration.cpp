#ifndef ALPACA__TAO_BOT_order_duration
#define ALPACA__TAO_BOT_order_duration

#include "tao_bot.h" // Alpaca::TaoBot
#include <ctime>     // std::time

int Alpaca::TaoBot::order_duration(const order_t *order_ptr) {
  if (!order_ptr) {
    return 0;
  }

  return std::time(nullptr) - order_ptr->timestamp;
}

#endif
