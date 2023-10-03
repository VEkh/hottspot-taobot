#ifndef ALPACA__TAO_BOT_read_predictions
#define ALPACA__TAO_BOT_read_predictions

#include "tao_bot.h" // Alpaca::TaoBot, fmt
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // puts

#include <string> // std::string

void Alpaca::TaoBot::read_predictions() {
  const std::string api_key = this->api_client.config.api_key;

  if (!this->five_min_predict.should_predict(api_key)) {
    return;
  }

  this->three_min_predict.get_fresh_predictions(this->current_epoch);

  if (api_key == "backtest-ml-3") {
    if (this->three_min_predict.predictions.empty() &&
        this->api_client.config.ml__on_demand_predictions) {
      std::cout << fmt.bold << fmt.yellow;
      puts("🤖 No fresh 3 Minute Predictions. Making new ones.");
      std::cout << fmt.reset << std::endl;

      this->three_min_predict.predict(this->current_epoch);
    }
  } else {
    this->five_min_predict.get_fresh_predictions(this->current_epoch);

    if (this->five_min_predict.predictions.empty() &&
        this->api_client.config.ml__on_demand_predictions) {
      std::cout << fmt.bold << fmt.yellow;
      puts("🤖 No fresh 5 Minute Predictions. Making new ones.");
      std::cout << fmt.reset << std::endl;

      this->five_min_predict.predict(this->current_epoch);
    }
  }
}

#endif
