#ifndef ALPACA__TAO_BOT_log_predictions
#define ALPACA__TAO_BOT_log_predictions

#include "tao_bot.h" // Alpaca::TaoBot

void Alpaca::TaoBot::log_predictions() {
  if (!this->five_min_predict.should_predict()) {
    return;
  }

  this->five_min_predict.log_predictions(this->current_epoch);
}

#endif
