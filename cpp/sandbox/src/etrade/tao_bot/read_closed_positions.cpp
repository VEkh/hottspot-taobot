#ifndef ETRADE__TAO_BOT_read_closed_positions
#define ETRADE__TAO_BOT_read_closed_positions

/*
 * ETrade::TaoBot
 * order_action_t
 * order_t
 * position_t
 */
#include "tao_bot.h"

#include "etrade/constants.cpp" // ETrade::constants
#include "etrade/deps.cpp"      // json
#include "etrade/utils.cpp"     // ETrade::utils
#include "lib/utils/io.cpp"     // utils::io
#include <stdexcept>            // std::invalid_argument
#include <vector>               // std::vector

std::vector<ETrade::t::position_t> ETrade::TaoBot::read_closed_positions() {
  order_t (*json_to_order)(json &) = [](json &order_json) -> order_t {
    std::string action = order_json["action"];

    order_t order;
    order.action = ETrade::utils::to_order_action_t(action.c_str());
    order.id = order_json["id"];
    order.profit = order_json["profit"];
    order.quantity = order_json["quantity"];
    order.timestamp = order_json["timestamp"];

    return order;
  };

  std::vector<position_t> positions = {};

  std::string filepath = std::string(APP_DIR) +
                         "/data/etrade/closed_positions/" +
                         std::string(this->symbol) + ".json";

  std::ifstream file;

  try {
    file = ::utils::io::read_file(filepath.c_str());
  } catch (std::invalid_argument &) {
    return positions;
  }

  json positions_json;
  file >> positions_json;

  for (json position_json : positions_json) {
    position_t position = {
        .close_order = json_to_order(position_json["close_order"]),
        .close_timestamp = position_json["close_timestamp"],
        .open_order = json_to_order(position_json["open_order"]),
    };

    positions.push_back(position);
  }

  return positions;
}

#endif
