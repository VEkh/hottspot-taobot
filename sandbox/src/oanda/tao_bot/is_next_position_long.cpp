#ifndef OANDA__TAO_BOT_is_next_position_long
#define OANDA__TAO_BOT_is_next_position_long

#include "tao_bot.h" // Oanda::TaoBot, order_action_t

bool Oanda::TaoBot::is_next_position_long() {
  return this->entry_reversal.type == reversal_type_t::REVERSAL_LOW;
};
#endif
