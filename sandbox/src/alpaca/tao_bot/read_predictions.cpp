#ifndef ALPACA__TAO_BOT_read_predictions
#define ALPACA__TAO_BOT_read_predictions

#include "tao_bot.h" // Alpaca::TaoBot, fmt
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf

#include <string> // std::string

void Alpaca::TaoBot::read_predictions() {
  const std::string api_key = this->api_client.config.api_key;

  if (!this->candle_predictor.should_predict()) {
    return;
  }

  this->candle_predictor.get_fresh_predictions(this->current_epoch);
  this->candle_predictor.set_consolidation_range(this->current_epoch);

  if (this->candle_predictor.should_on_demand_predict() &&
      this->candle_predictor.are_predictions_stale(this->current_epoch)) {
    std::cout << fmt.bold << fmt.yellow;
    printf("🤖 No fresh %i Minute Predictions. Making new ones.\n",
           this->candle_predictor.duration_minutes);
    std::cout << fmt.reset << std::endl;

    this->candle_predictor.predict(this->current_epoch);
  }
}

#endif
