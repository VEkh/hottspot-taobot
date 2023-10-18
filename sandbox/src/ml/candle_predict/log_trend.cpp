#ifndef ML__CANDLE_PREDICT_log_trend
#define ML__CANDLE_PREDICT_log_trend

#include "candle_predict.h"   // ML::CandlePredict, candle_t, fmt
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include <iostream>           // std::cout, std::endl
#include <list>               // std::list
#include <stdio.h>            // printf

void ML::CandlePredict::log_trend() {
  if (this->trend_candles.size() < this->TREND_WINDOW_SIZE) {
    std::cout << fmt.bold << fmt.yellow;
    puts("📈❌ No trend established.");
    std::cout << fmt.reset << std::endl;

    return;
  }

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("📈 Price Trend\n");

  std::list<candle_t>::iterator it;

  for (it = this->trend_candles.begin(); it != this->trend_candles.end();
       it++) {
    Formatted::Stream log_color = Formatted::int_to_stream(it->trend());

    const std::string timestamp_str =
        ::utils::time_::date_string(it->closed_at, "%H:%M", "America/Chicago");

    std::cout << fmt.bold << fmt.yellow;
    if (it != this->trend_candles.begin()) {
      printf(" • ");
    }

    std::cout << fmt.bold << log_color;
    printf("%.2f (%s)", it->close, timestamp_str.c_str());
    std::cout << fmt.reset;
  }

  std::cout << fmt.reset << std::endl << std::endl;
}

#endif
