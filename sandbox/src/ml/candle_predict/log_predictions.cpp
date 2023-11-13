#ifndef ML__CANDLE_PREDICT_log_predictions
#define ML__CANDLE_PREDICT_log_predictions

#include "are_predictions_stale.cpp" // are_predictions_stale
#include "candle_predict.h"          // ML::CandlePredict, fmt, prediction_t
#include "latest_predictions.cpp"    // latest_predictions
#include "lib/formatted.cpp"         // Formatted
#include "lib/utils/integer.cpp"     // ::utils::integer_
#include "predict_action.cpp"        // predict_action
#include <iostream>                  // std::cout, std::endl
#include <list>                      // std::list
#include <stdio.h>                   // printf
#include <string>                    // std::string

void ML::CandlePredict::log_predictions(const double current_epoch) {
  if (this->predictions.empty()) {
    std::cout << fmt.bold << fmt.cyan;
    printf("🤖💀 No %i Minute Predictions to log.\n",
           this->duration_minutes);
    std::cout << fmt.reset << std::endl;

    return;
  }

  if (are_predictions_stale(current_epoch)) {
    std::cout << fmt.bold << fmt.cyan;
    printf("🤖💀 No Current %i Minute Predictions to log.\n",
           this->duration_minutes);
    std::cout << fmt.reset << std::endl;

    return;
  }

  std::cout << fmt.bold << fmt.underline << fmt.cyan;
  printf("🤖 %i Minute Predictions (Close)", this->duration_minutes);
  std::cout << fmt.reset;

  const Formatted::Stream inv_predictions_color =
      this->config.inverse_predictions ? fmt.green : fmt.red;

  const std::string inv_predictions_text =
      this->config.inverse_predictions ? "ON" : "OFF";

  std::cout << fmt.bold << fmt.yellow;
  std::cout << " Inverse: " << inv_predictions_color << inv_predictions_text
            << std::endl;

  std::list<prediction_t> latest_predictions_ = latest_predictions().second;

  std::list<prediction_t>::iterator it;

  for (it = latest_predictions_.begin(); it != latest_predictions_.end();
       it++) {
    Formatted::Stream log_color = fmt.yellow;

    const prediction_t prediction = *it;

    std::cout << fmt.bold << log_color;

    if (it != latest_predictions_.begin()) {
      printf("\n");
    }

    log_color = predict_action(prediction) == order_action_t::SELL ? fmt.red
                                                                   : fmt.green;

    const std::string timestamp_str = ::utils::time_::date_string(
        prediction.candle.closed_at, "%H:%M", "America/Chicago");

    std::cout << log_color;
    printf("%s (%s): %.2f", prediction.model_name.c_str(),
           timestamp_str.c_str(), prediction.close);
  }

  std::cout << fmt.reset << std::endl << std::endl;
}

#endif
