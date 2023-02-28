#ifndef ALPACA__QUOTE_read_price_movement
#define ALPACA__QUOTE_read_price_movement

#include "deps.cpp"         // json
#include "lib/utils/io.cpp" // ::utils::io
#include "quote.h"          // Alpaca::Quote
#include <fstream>          // std::ifstream
#include <stdexcept>        // std::invalid_argument
#include <string>           // std::string

Alpaca::Quote::price_movement_t
Alpaca::Quote::read_price_movement(const std::string symbol) {
  const std::string filepath =
      std::string(DATA_DIR) + "/alpaca/price_movement/" + symbol + ".json";

  std::ifstream file;
  json persisted_data;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> persisted_data;
    file.close();
  } catch (nlohmann::detail::parse_error &) {
  } catch (std::invalid_argument &) {
  }

  if (persisted_data.empty()) {
    return price_movement_t();
  }

  if (persisted_data.contains("short_term_three_minute_one_second_variance")) {
    const double short_term_average =
        persisted_data["short_term_three_minute_one_second_variance"]
                      ["average"];
    const int short_term_count =
        persisted_data["short_term_three_minute_one_second_variance"]["count"];

    this->price_movements[symbol]
        .short_term_three_minute_one_second_variance.average =
        short_term_average;
    this->price_movements[symbol]
        .short_term_three_minute_one_second_variance.count = short_term_count;
  }

  if (persisted_data.contains("three_minute_one_second_variance")) {
    const double average =
        persisted_data["three_minute_one_second_variance"]["average"];
    const int count =
        persisted_data["three_minute_one_second_variance"]["count"];

    this->price_movements[symbol].three_minute_one_second_variance.average =
        average;
    this->price_movements[symbol].three_minute_one_second_variance.count =
        count;
  }

  return this->price_movements[symbol];
}

#endif
