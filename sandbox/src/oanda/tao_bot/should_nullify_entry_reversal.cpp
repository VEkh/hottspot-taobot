// TODO: Decide
#ifndef OANDA__TAO_BOT_should_nullify_entry_reversal
#define OANDA__TAO_BOT_should_nullify_entry_reversal

#include "tao_bot.h" // Oanda::TaoBot, order_t, reversal_t

bool Oanda::TaoBot::should_nullify_entry_reversal() {
  // TODO: Decide
  if (!this->api_client.config.should_reverse_at_trend_slip &&
      !this->closed_positions.empty()) {
    const reversal_t record_high =
        latest_record_as_reversal(reversal_type_t::REVERSAL_HIGH);

    const reversal_t record_low =
        latest_record_as_reversal(reversal_type_t::REVERSAL_LOW);

    return record_high.at < this->current_trend.at &&
           record_low.at < this->current_trend.at;
  }

  const int current_epoch_minute = this->current_epoch / 60;
  const int trend_at_minute = this->current_trend.at / 60;

  return current_epoch_minute < trend_at_minute;
}

#endif
