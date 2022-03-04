#ifndef OANDA__TAO_BOT_load_price_movement
#define OANDA__TAO_BOT_load_price_movement

/*
 * Oanda::TaoBot
 * order_t
 * position_t
 */
#include "tao_bot.h"

#include "deps.cpp"         // json
#include "lib/utils/io.cpp" // ::utils::io
#include <fstream>          // std::ifstream
#include <stdexcept>        // std::invalid_argument

void Oanda::TaoBot::load_price_movement() {
  const std::string filepath = std::string(APP_DIR) +
                               "/data/oanda/price_movement/" +
                               std::string(this->symbol) + ".json";

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

  if (!persisted_data.contains("three_minute_one_second_variance")) {
    return;
  }

  const double average =
      persisted_data["three_minute_one_second_variance"]["average"];

  const int count = persisted_data["three_minute_one_second_variance"]["count"];

  this->price_movement.three_minute_one_second_variance.average = average;
  this->price_movement.three_minute_one_second_variance.count = count;
}

#endif
