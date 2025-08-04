#ifndef OANDA__TAO_BOT_margin_normalization_factor
#define OANDA__TAO_BOT_margin_normalization_factor

#include "tao_bot.h" // Oanda::TaoBot

double Oanda::TaoBot::margin_normalization_factor() {
  const double base_price_action =
      this->api_client.config.margin_normalization_base_price_action;

  const double margin_multiplier = this->api_client.config.margin_multiplier;

  if (!margin_multiplier) {
    return 1.0;
  }

  if (!base_price_action) {
    return 1.0;
  }

  if (this->warm_up_candle.range_open_percent() < 0) {
    return 1.0;
  }

  const double ref_price_action = this->day_candle.range_open_percent();
  double factor = (base_price_action * 100.0) / ref_price_action;

  const double max_factor = 1.0;

  return std::min(max_factor, factor);
}

#endif
