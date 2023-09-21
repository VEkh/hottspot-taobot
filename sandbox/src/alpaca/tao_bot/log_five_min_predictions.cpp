#ifndef ALPACA__TAO_BOT_log_five_min_predictions
#define ALPACA__TAO_BOT_log_five_min_predictions

#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/integer.cpp" // ::utils::integer_
#include "tao_bot.h"             // Alpaca::TaoBot, fmt
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Alpaca::TaoBot::log_five_min_predictions() {
  if (this->five_min_predictions.empty()) {
    std::cout << fmt.bold << fmt.cyan;
    puts("🤖💀 No 5 Minute Predictions to log.");
    std::cout << fmt.reset << std::endl;

    return;
  }

  std::cout << fmt.bold << fmt.underline << fmt.cyan;
  printf("🤖 5 Minute Predictions (Close)\n");
  std::cout << fmt.reset;

  std::list<five_min_prediction_t>::iterator it;

  for (it = this->five_min_predictions.begin();
       it != this->five_min_predictions.end(); it++) {
    Formatted::Stream log_color = fmt.yellow;

    const five_min_prediction_t prediction = *it;

    std::cout << fmt.bold << log_color;

    if (it != this->five_min_predictions.begin()) {
      printf(" • ");
    }

    log_color =
        prediction.close < prediction.candle.close ? fmt.red : fmt.green;

    std::cout << log_color;
    printf("%s: %.2f", prediction.model_name.c_str(), prediction.close);
  }

  std::cout << fmt.reset << std::endl << std::endl;
}

#endif
