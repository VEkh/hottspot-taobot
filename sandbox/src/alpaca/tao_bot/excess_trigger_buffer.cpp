#ifndef ALPACA__TAO_BOT_excess_trigger_buffer
#define ALPACA__TAO_BOT_excess_trigger_buffer

#include "tao_bot.h" // Alpaca::TaoBot

double Alpaca::TaoBot::excess_trigger_buffer() {
  return this->EXCESS_TRIGGER_BUFFER_COEFFICIENT *
         this->avg_one_sec_variances.running;
}

#endif
