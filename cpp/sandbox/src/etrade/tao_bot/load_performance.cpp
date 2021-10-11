#ifndef ETRADE__TAO_BOT_load_performance
#define ETRADE__TAO_BOT_load_performance

/*
 * ETrade::TaoBot
 * order_t
 * position_t
 */
#include "tao_bot.h"

#include "etrade/deps.cpp"  // json
#include "etrade/utils.cpp" // ETrade::utils
#include "lib/utils/io.cpp" // ::utils::io
#include <stdexcept>        // std::invalid_argument
#include <vector>           // std::vector

void ETrade::TaoBot::load_performance() {
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

  this->closed_positions = {};

  std::string filepath = std::string(APP_DIR) + "/data/etrade/performance/" +
                         std::string(this->symbol) + ".json";

  std::ifstream file;

  try {
    file = ::utils::io::read_file(filepath.c_str());
  } catch (std::invalid_argument &) {
    return;
  }

  json persisted_data;
  file >> persisted_data;
  file.close();

  double max_balance_ = 0.00;
  json positions_json = json::array();

  if (persisted_data.contains("max_balance")) {
    max_balance_ = persisted_data["max_balance"];
  }

  if (persisted_data.contains("positions")) {
    positions_json = persisted_data["positions"];
  }

  for (json position_json : positions_json) {
    position_t position = {
        .close_order = json_to_order(position_json["close_order"]),
        .close_timestamp = position_json["close_timestamp"],
        .open_order = json_to_order(position_json["open_order"]),
    };

    this->closed_positions.push_back(position);
  }

  this->performance.max_balance = max_balance_;
}

#endif
