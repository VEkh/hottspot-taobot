#ifndef ALPACA__TAO_BOT_advance_current_time
#define ALPACA__TAO_BOT_advance_current_time

#include "tao_bot.h" // Alpaca::TaoBot
#include <time.h>    // time
#include <unistd.h>  // usleep

void Alpaca::TaoBot::advance_current_time() {
  if (this->api_client.config.is_backtest) {
    this->api_client.config.current_time =
        this->api_client.config.current_time + 0.5;
  } else {
    usleep(5e5);

    this->api_client.config.current_time = time(nullptr);
  }
}

#endif
