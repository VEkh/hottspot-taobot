#ifndef ALPACA__TAO_BOT_load_price_movement
#define ALPACA__TAO_BOT_load_price_movement

#include "deps.cpp"         // json
#include "lib/utils/io.cpp" // ::utils::io
#include "tao_bot.h"        // Alpaca::TaoBot
#include <fstream>          // std::ifstream
#include <stdexcept>        // std::invalid_argument
#include <string>           // std::string

void Alpaca::TaoBot::load_price_movement() {
  json persisted_data = load_price_movement(this->symbol);

  if (persisted_data.empty()) {
    return;
  }

  if (persisted_data.contains("short_term_three_minute_one_second_variance")) {
    const double short_term_average =
        persisted_data["short_term_three_minute_one_second_variance"]
                      ["average"];
    const int short_term_count =
        persisted_data["short_term_three_minute_one_second_variance"]["count"];

    this->price_movement.short_term_three_minute_one_second_variance.average =
        short_term_average;
    this->price_movement.short_term_three_minute_one_second_variance.count =
        short_term_count;
  }

  if (persisted_data.contains("three_minute_one_second_variance")) {
    const double average =
        persisted_data["three_minute_one_second_variance"]["average"];
    const int count =
        persisted_data["three_minute_one_second_variance"]["count"];

    this->price_movement.three_minute_one_second_variance.average = average;
    this->price_movement.three_minute_one_second_variance.count = count;
  }
}

json Alpaca::TaoBot::load_price_movement(const std::string symbol_) {
  const std::string filepath = std::string(APP_DIR) +
                               "/data/alpaca/price_movement/" +
                               std::string(symbol_) + ".json";

  std::ifstream file;
  json persisted_data;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> persisted_data;
    file.close();
  } catch (nlohmann::detail::parse_error &) {
  } catch (std::invalid_argument &) {
  }

  return persisted_data;
}

#endif
