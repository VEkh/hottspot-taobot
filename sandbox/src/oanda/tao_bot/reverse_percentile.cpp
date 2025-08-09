#ifndef OANDA__TAO_BOT_reverse_percentile
#define OANDA__TAO_BOT_reverse_percentile

#include "tao_bot.h" // Oanda::TaoBot

double Oanda::TaoBot::reverse_percentile() {
  const int reverse_percentile_id =
      this->api_client.config.trade_setup_reverse_percentile_id;

  const int stop_profit_id = this->api_client.config.trade_setup_stop_profit_id;

  std::map<int, double> id_map = {
      {1, 0.0},
      {2, 50.0},
  };

  if (!this->open_order_ptr) {
    return id_map[1];
  }

  if (!reverse_percentile_id) {
    return id_map[1];
  }

  if (stop_profit_id == 2) {
    if (this->open_order_ptr->max_profit >= abs(this->exit_prices.stop_loss)) {
      return id_map[2];
    }

    return id_map[1];
  }

  return id_map[reverse_percentile_id];
}

#endif
