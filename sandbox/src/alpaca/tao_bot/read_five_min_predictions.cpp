#ifndef ALPACA__TAO_BOT_read_five_min_predictions
#define ALPACA__TAO_BOT_read_five_min_predictions

#include "tao_bot.h" // Alpaca::TaoBot, fmt
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // puts

void Alpaca::TaoBot::read_five_min_predictions() {
  this->five_min_predict.get_fresh_predictions(this->current_epoch);

  if (this->five_min_predict.predictions.empty()) {
    std::cout << fmt.bold << fmt.yellow;
    puts("🤖 No 5 Minute Predictions. Making new ones.");
    std::cout << fmt.reset << std::endl;

    this->five_min_predict.predict(this->current_epoch);
  }
}

#endif
