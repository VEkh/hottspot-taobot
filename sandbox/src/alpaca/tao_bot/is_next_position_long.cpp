#ifndef ALPACA__TAO_BOT_is_next_position_long
#define ALPACA__TAO_BOT_is_next_position_long

#include "tao_bot.h" // Alpaca::TaoBot reversal_type_t

bool Alpaca::TaoBot::is_next_position_long() {
  return this->entry_reversal.type == reversal_type_t::REVERSAL_LOW;
};

#endif
