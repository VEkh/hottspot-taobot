// TODO: Decide
#ifndef OANDA__TAO_BOT_should_nullify_entry_reversal
#define OANDA__TAO_BOT_should_nullify_entry_reversal

#include "tao_bot.h" // Oanda::TaoBot, order_t, reversal_t

bool Oanda::TaoBot::should_nullify_entry_reversal() {
  // TODO: Decide
  if (!this->api_client.config.should_trade_into_reversal &&
      !this->closed_positions.empty()) {
    const position_t last_position = this->closed_positions.back();

    if (last_position.open_order.min_profit >
        last_position.open_order.stop_loss) {
      return true;
    }
  }

  const int current_epoch_minute = this->current_epoch / 60;
  const int trend_at_minute = this->current_trend.at / 60;

  return current_epoch_minute < trend_at_minute;
}

#endif
