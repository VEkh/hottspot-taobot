#ifndef ML__CANDLE_PREDICT_log_correct_predictions
#define ML__CANDLE_PREDICT_log_correct_predictions

#include "candle_predict.h" // ML::CandlePredict, fmt, order_action_t, prediction_t
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "predict_action.cpp" // predict_action
#include <algorithm>          // std::max
#include <iostream>           // std::cout, std::endl
#include <iterator>           // std::advance
#include <list>               // std::list
#include <map>                // std::map
#include <stdio.h>            // printf
#include <string>             // std::string

void ML::CandlePredict::log_correct_predictions() {
  if (this->correct_predictions.empty()) {
    std::cout << fmt.bold << fmt.cyan;
    printf("🤖😶 No correct predictions\n");
    std::cout << fmt.reset << std::endl;

    return;
  }

  const int correct_predictions_n = this->correct_predictions.size();
  const int predictions_n = this->predictions.size();

  const double accuracy =
      100.0 * ((double)correct_predictions_n / (double)predictions_n);
  const int limit = 5;

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("🤖✅ Last %i Correct Predictions (Accuracy: %i/%i • %.2f%%)\n",
         limit, correct_predictions_n, predictions_n, accuracy);
  std::cout << fmt.reset;

  std::map<double, std::list<prediction_t>>::iterator it =
      this->correct_predictions.end();

  const int offset = std::min((int)this->correct_predictions.size(), limit);
  std::advance(it, -offset);

  for (; it != this->correct_predictions.end(); it++) {
    const std::list<prediction_t> predictions_ = it->second;
    const order_action_t predicted_action = predict_action(predictions_);

    Formatted::Stream log_color =
        predicted_action == order_action_t::BUY ? fmt.green : fmt.red;

    const std::string timestamp_str =
        ::utils::time_::date_string(it->first, "%H:%M", "America/Chicago");

    std::cout << fmt.bold << log_color;
    printf("%.2f (%s)", predictions_.front().candle.close,
           timestamp_str.c_str());

    std::cout << fmt.bold << fmt.yellow;
    if (std::next(it) != this->correct_predictions.end()) {
      printf(" • ");
    }
    std::cout << fmt.reset;
  }

  std::cout << std::endl << std::endl;
}

#endif
