#ifndef ALPACA__TAO_BOT_advance_current_epoch
#define ALPACA__TAO_BOT_advance_current_epoch

#include "tao_bot.h" // Alpaca::TaoBot
#include <time.h>    // time
#include <unistd.h>  // usleep

void Alpaca::TaoBot::advance_current_epoch() {
  if (this->api_client.config.is_backtest) {
    this->api_client.config.current_epoch =
        this->api_client.config.current_epoch + 0.5;

    this->api_client.backtest_config.slow_query_countdown += 1;
  } else {
    usleep(5e5);

    this->api_client.config.current_epoch = time(nullptr);
  }
}

#endif
