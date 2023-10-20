#ifndef ML__CANDLE_PREDICT_log_consolidation_range
#define ML__CANDLE_PREDICT_log_consolidation_range

#include "candle_predict.h" // ML::CandlePredict, consolidation_range_t, fmt
#include "is_consolidation_range_set.cpp" // is_consolidation_range_set
#include "lib/utils/time.cpp"             // ::utils::time_
#include <iostream>                       // std::cout, std::endl
#include <stdio.h>                        // printf

void ML::CandlePredict::log_consolidation_range(
    const log_consolidation_range_args_t args) {
  const double current_mid = args.current_mid;
  const double range_buffer = args.range_buffer;

  if (!is_consolidation_range_set()) {
    std::cout << fmt.bold << fmt.yellow;
    puts("📊❌ No Consolidation Range");
    std::cout << fmt.reset << std::endl;

    return;
  }

  std::string beyond_range_str = "";
  std::string mid_location_icon = "✅";

  if (current_mid > this->consolidation_range.high) {
    mid_location_icon = "👆";
  } else if (current_mid < this->consolidation_range.low) {
    mid_location_icon = "👇";
  }

  if (current_mid > this->consolidation_range.high + range_buffer ||
      current_mid < this->consolidation_range.low - range_buffer) {
    beyond_range_str = "🌟";
  }

  const bool is_in_range = current_mid < this->consolidation_range.high &&
                           current_mid > this->consolidation_range.low;

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("📊 Consolidation Range %s%s", mid_location_icon.c_str(),
         beyond_range_str.c_str());
  std::cout << fmt.reset << std::endl;

  const std::string high_at_str = ::utils::time_::date_string(
      this->consolidation_range.high_at, "%H:%M", "America/Chicago");

  const std::string low_at_str = ::utils::time_::date_string(
      this->consolidation_range.low_at, "%H:%M", "America/Chicago");

  std::cout << fmt.bold << fmt.green;
  printf("High (%s): %.2f", high_at_str.c_str(),
         this->consolidation_range.high);

  std::cout << fmt.yellow << " • ";

  std::cout << fmt.bold << fmt.red;
  printf("Low (%s): %.2f\n", low_at_str.c_str(), this->consolidation_range.low);
  std::cout << fmt.reset << std::endl;
}

#endif
