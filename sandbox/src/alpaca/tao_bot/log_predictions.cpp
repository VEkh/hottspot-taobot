#ifndef ALPACA__TAO_BOT_log_predictions
#define ALPACA__TAO_BOT_log_predictions

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::log_predictions() {
  if (!this->five_min_predict.should_predict(this->api_client.config.api_key)) {
    return;
  }

  this->three_min_predict.log_predictions();
  this->five_min_predict.log_predictions();
}

#endif
