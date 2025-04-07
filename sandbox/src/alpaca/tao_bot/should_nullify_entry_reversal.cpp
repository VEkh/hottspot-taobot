// TODO: Decide
#ifndef ALPACA__TAO_BOT_should_nullify_entry_reversal
#define ALPACA__TAO_BOT_should_nullify_entry_reversal

#include "latest_record_as_reversal.cpp" // latest_record_as_reversal
#include "tao_bot.h"                     // Alpaca::TaoBot, order_t, reversal_t

bool Alpaca::TaoBot::should_nullify_entry_reversal() {
  if (this->api_client.config.should_await_record_break &&
      (!this->api_client.config.should_stop_profit_once &&
       this->has_stopped_profit)) {
    const reversal_t record_high =
        latest_record_as_reversal(reversal_type_t::REVERSAL_HIGH);

    const reversal_t record_low =
        latest_record_as_reversal(reversal_type_t::REVERSAL_LOW);

    const order_t last_close_order = this->closed_positions.back().close_order;

    return record_high.at < last_close_order.timestamp &&
           record_low.at < last_close_order.timestamp;
  }

  const int current_epoch_minute = this->current_epoch / 60;
  const int trend_at_minute = this->current_trend.at / 60;

  return current_epoch_minute < trend_at_minute;
}

#endif
