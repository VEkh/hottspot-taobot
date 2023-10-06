#ifndef ALPACA__TAO_BOT_read_predictions
#define ALPACA__TAO_BOT_read_predictions

#include "tao_bot.h" // Alpaca::TaoBot, fmt
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf

#include <string> // std::string

void Alpaca::TaoBot::read_predictions() {
  const std::string api_key = this->api_client.config.api_key;

  if (!this->five_min_predict.should_predict()) {
    return;
  }

  this->ten_min_predict.get_fresh_predictions(this->current_epoch);

  if (api_key == "backtest-ml-10") {
    if (this->ten_min_predict.predictions.empty() &&
        this->ten_min_predict.should_on_demand_predict()) {
      std::cout << fmt.bold << fmt.yellow;
      printf("🤖 No fresh %i Minute Predictions. Making new ones.\n",
             this->ten_min_predict.duration_minutes);
      std::cout << fmt.reset << std::endl;

      this->ten_min_predict.predict(this->current_epoch);
    }
  } else {
    this->five_min_predict.get_fresh_predictions(this->current_epoch);

    if (this->five_min_predict.predictions.empty() &&
        this->five_min_predict.should_on_demand_predict()) {
      std::cout << fmt.bold << fmt.yellow;
      printf("🤖 No fresh %i Minute Predictions. Making new ones.\n",
             this->five_min_predict.duration_minutes);
      std::cout << fmt.reset << std::endl;

      this->five_min_predict.predict(this->current_epoch);
    }
  }
}

#endif
