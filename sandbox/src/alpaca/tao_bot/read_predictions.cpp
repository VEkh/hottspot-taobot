#ifndef ALPACA__TAO_BOT_read_predictions
#define ALPACA__TAO_BOT_read_predictions

#include "tao_bot.h" // Alpaca::TaoBot, fmt
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // puts

void Alpaca::TaoBot::read_predictions() {
  if (!this->five_min_predict.should_predict(this->api_client.config.api_key)) {
    return;
  }

  this->five_min_predict.get_fresh_predictions(this->current_epoch);

  if (this->five_min_predict.predictions.empty()) {
    std::cout << fmt.bold << fmt.yellow;
    puts("🤖 No 5 Minute Predictions. Making new ones.");
    std::cout << fmt.reset << std::endl;

    this->five_min_predict.predict(this->current_epoch);
  }
}

#endif
