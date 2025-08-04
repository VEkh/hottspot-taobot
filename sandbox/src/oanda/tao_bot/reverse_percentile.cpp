#ifndef OANDA__TAO_BOT_reverse_percentile
#define OANDA__TAO_BOT_reverse_percentile

#include "tao_bot.h" // Oanda::TaoBot

double Oanda::TaoBot::reverse_percentile() {
  const double primary_reverse_percentile =
      this->api_client.config.reverse_percentile;

  const double secondary_reverse_percentile =
      this->api_client.config.secondary_reverse_percentile;

  if (!this->open_order_ptr) {
    return primary_reverse_percentile;
  }

  if (!secondary_reverse_percentile) {
    return primary_reverse_percentile;
  }

  if (this->api_client.config.stop_profit_version == 0.2 &&
      this->open_order_ptr->max_profit >= abs(this->exit_prices.stop_loss)) {
    return secondary_reverse_percentile;
  }

  return primary_reverse_percentile;
}

#endif
