#ifndef ML__CANDLE_PREDICT_log_opposing_predictions
#define ML__CANDLE_PREDICT_log_opposing_predictions

#include "candle_predict.h" // ML::CandlePredict, fmt, order_action_t, predictions_t
#include "lib/formatted.cpp"  // Formatted
#include "predict_action.cpp" // predict_action
#include <iostream>           // std::cout, std::endl
#include <list>               // std::list
#include <map>                // std::map
#include <stdio.h>            // printf
#include <string>             // std::string

void ML::CandlePredict::log_opposing_predictions() {
  if (this->opposing_predictions.empty()) {
    std::cout << fmt.bold << fmt.cyan;
    printf("😶 No opposing predictions\n");
    std::cout << fmt.reset << std::endl;

    return;
  }

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("🤖⏪ Correct Opposing Prediction Closes\n");
  std::cout << fmt.reset;

  std::map<double, predictions_t>::iterator it =
      this->opposing_predictions.begin();

  for (; it != this->opposing_predictions.end(); it++) {
    const predictions_t predictions_ = it->second;
    const order_action_t predicted_action =
        predict_action(predictions_.predictions);

    Formatted::Stream log_color =
        predicted_action == order_action_t::BUY ? fmt.green : fmt.red;

    const std::string timestamp_str =
        ::utils::time_::date_string(it->first, "%H:%M", "America/Chicago");

    std::cout << fmt.bold << fmt.yellow;
    if (it != this->opposing_predictions.begin()) {
      printf(" • ");
    }

    std::cout << fmt.bold << log_color;
    printf("%.2f (%s)", predictions_.predictions.front().candle.close,
           timestamp_str.c_str());
    std::cout << fmt.reset;
  }

  std::cout << std::endl << std::endl;
}

#endif
