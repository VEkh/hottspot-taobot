#ifndef ALPACA__TAO_BOT_runtime
#define ALPACA__TAO_BOT_runtime

#include "tao_bot.h" // Alpaca::TaoBot
#include <ctime>     // std::time

int Alpaca::TaoBot::runtime() {
  return this->api_client.config.current_epoch - this->started_at;
}

#endif
