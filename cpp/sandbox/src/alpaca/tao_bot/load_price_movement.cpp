#ifndef ALPACA__TAO_BOT_load_price_movement
#define ALPACA__TAO_BOT_load_price_movement

/*
 * Alpaca::TaoBot
 * order_t
 * position_t
 */
#include "tao_bot.h"

#include "deps.cpp"         // json
#include "lib/utils/io.cpp" // ::utils::io
#include <fstream>          // std::ifstream
#include <stdexcept>        // std::invalid_argument
#include <string>           // std::string

void Alpaca::TaoBot::load_price_movement(const std::string &symbol_) {
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
    return;
  } catch (std::invalid_argument &) {
    return;
  }

  double average, short_term_average;
  int count, short_term_count;

  if (persisted_data.contains("short_term_three_minute_one_second_variance")) {
    short_term_average =
        persisted_data["short_term_three_minute_one_second_variance"]
                      ["average"];
    short_term_count =
        persisted_data["short_term_three_minute_one_second_variance"]["count"];

    this->price_movement.short_term_three_minute_one_second_variance.average =
        short_term_average;
    this->price_movement.short_term_three_minute_one_second_variance.count =
        short_term_count;
  }

  if (persisted_data.contains("three_minute_one_second_variance")) {
    average = persisted_data["three_minute_one_second_variance"]["average"];
    count = persisted_data["three_minute_one_second_variance"]["count"];

    this->price_movement.three_minute_one_second_variance.average = average;
    this->price_movement.three_minute_one_second_variance.count = count;
  }
}

#endif
