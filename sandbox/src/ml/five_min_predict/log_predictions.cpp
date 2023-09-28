#ifndef ML__FIVE_MIN_PREDICT_log_predictions
#define ML__FIVE_MIN_PREDICT_log_predictions

#include "five_min_predict.h"    // ML::FiveMinPredict, fmt, prediction_t
#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/integer.cpp" // ::utils::integer_
#include "predict_action.cpp"    // predict_action
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void ML::FiveMinPredict::log_predictions() {
  if (this->predictions.empty()) {
    std::cout << fmt.bold << fmt.cyan;
    puts("🤖💀 No 5 Minute Predictions to log.");
    std::cout << fmt.reset << std::endl;

    return;
  }

  std::cout << fmt.bold << fmt.underline << fmt.cyan;
  printf("🤖 5 Minute Predictions (Close)\n");
  std::cout << fmt.reset;

  std::list<prediction_t>::iterator it;

  for (it = this->predictions.begin(); it != this->predictions.end(); it++) {
    Formatted::Stream log_color = fmt.yellow;

    const prediction_t prediction = *it;

    std::cout << fmt.bold << log_color;

    if (it != this->predictions.begin()) {
      printf(" • ");
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
