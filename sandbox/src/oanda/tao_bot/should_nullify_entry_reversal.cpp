// TODO: Decide
#ifndef OANDA__TAO_BOT_should_nullify_entry_reversal
#define OANDA__TAO_BOT_should_nullify_entry_reversal

#include "tao_bot.h" // Oanda::TaoBot, order_t, reversal_t

bool Oanda::TaoBot::should_nullify_entry_reversal() {
  const int current_epoch_minute = this->current_epoch / 60;
  const int trend_at_minute = this->current_trend.at / 60;

  return current_epoch_minute < trend_at_minute;
}

#endif
