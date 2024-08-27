// TODO: Decide
#ifndef ALPACA__TAO_BOT_set_should_stop_loss
#define ALPACA__TAO_BOT_set_should_stop_loss

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::set_should_stop_loss() {
  if (!this->api_client.config.is_should_stop_loss_dynamic) {
    return;
  }

  if (!this->closed_positions.empty()) {
    return;
  }

  if (this->open_order_ptr) {
    return;
  }

  const double avg = this->price_action_stats.avg;
  const double std = this->price_action_stats.std;

  const double avg_delta_sigma_multiple =
      std ? (this->day_candle.range_open_percent() - avg) / std : 0;

  this->should_stop_loss = avg_delta_sigma_multiple <= 0;
}

#endif
