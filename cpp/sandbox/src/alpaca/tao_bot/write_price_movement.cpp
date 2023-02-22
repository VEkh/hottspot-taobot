#ifndef ALPACA__TAO_BOT_write_price_movement
#define ALPACA__TAO_BOT_write_price_movement

#include "deps.cpp"          // _json, json
#include "lib/formatted.cpp" // Formatted
#include "lib/utils/io.cpp"  // utils::io
#include "tao_bot.h"         // Alpaca::TaoBot, fmt, price_movement_t
#include <iostream>          // std::cout, std::endl
#include <stdio.h>           // puts
#include <string>            // std::string

void Alpaca::TaoBot::write_price_movement() {
  try {
    const std::string filepath = std::string(DATA_DIR) +
                                 "/alpaca/price_movement/" +
                                 std::string(this->symbol) + ".json";

    json price_movement_json = R"(
      {
        "short_term_three_minute_one_second_variance": {
          "average": 0.00,
          "count": 0
        },
        "three_minute_one_second_variance": {
          "average": 0.00,
          "count": 0
        }
      }
    )"_json;

    price_movement_json["short_term_three_minute_one_second_variance"]
                       ["average"] =
                           this->price_movement
                               .short_term_three_minute_one_second_variance
                               .average;
    price_movement_json["short_term_three_minute_one_second_variance"]
                       ["count"] =
                           this->price_movement
                               .short_term_three_minute_one_second_variance
                               .count;
    price_movement_json["three_minute_one_second_variance"]["average"] =
        this->price_movement.three_minute_one_second_variance.average;
    price_movement_json["three_minute_one_second_variance"]["count"] =
        this->price_movement.three_minute_one_second_variance.count;

    ::utils::io::write_to_file(price_movement_json.dump(2), filepath.c_str());
  } catch (nlohmann::detail::parse_error &) {
    const std::string error_message = Formatted::error_message(
        std::string("ALPACA__TAO_BOT_write_price_movement") +
        ": Parse error while writing price movement.");

    puts(error_message.c_str());
    std::cout << fmt.reset << std::endl;

    return write_price_movement();
  }
}

#endif
