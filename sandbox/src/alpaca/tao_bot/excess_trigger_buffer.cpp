#ifndef ALPACA__TAO_BOT_excess_trigger_buffer
#define ALPACA__TAO_BOT_excess_trigger_buffer

#include "tao_bot.h" // Alpaca::TaoBot
#include <math.h>    // abs

double Alpaca::TaoBot::excess_trigger_buffer() {
  return abs(this->api_client.config.stop_loss_ratio) *
         this->avg_one_sec_variances.running;
}

#endif
