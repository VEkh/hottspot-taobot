#ifndef OANDA__TAO_BOT_load_performance
#define OANDA__TAO_BOT_load_performance

/*
 * Oanda::TaoBot
 * order_t
 * position_t
 */
#include "tao_bot.h"

#include "deps.cpp"         // json, nlohmann
#include "lib/utils/io.cpp" // ::utils::io
#include "oanda/utils.cpp"  // Oanda::utils
#include <fstream>          // std::ifstream
#include <stdexcept>        // std::invalid_argument
#include <string>           // std::string
#include <vector>           // std::vector

void Oanda::TaoBot::load_performance() {
  order_t (*json_to_order)(json &) = [](json &order_json) -> order_t {
    std::string action = order_json["action"];

    order_t order;
    order.action = Oanda::utils::to_order_action_t(action.c_str());
    order.id = order_json["id"];
    order.profit = order_json["profit"];
    order.quantity = order_json["quantity"];
    order.timestamp = order_json["timestamp"];

    return order;
  };

  this->closed_positions = {};

  const std::string filepath = std::string(DATA_DIR) + "/oanda/performance/" +
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

  json positions_json = json::array();

  if (persisted_data.contains("current_balance")) {
    this->performance.current_balance = persisted_data["current_balance"];
  }

  if (persisted_data.contains("current_loss_streak_balance")) {
    this->performance.current_loss_streak_balance =
        persisted_data["current_loss_streak_balance"];
  }

  if (persisted_data.contains("max_balance")) {
    this->performance.max_balance = persisted_data["max_balance"];
  }

  if (persisted_data.contains("positions")) {
    positions_json = persisted_data["positions"];
  }

  for (json position_json : positions_json) {
    position_t position = {
        .close_order = json_to_order(position_json["close_order"]),
        .open_order = json_to_order(position_json["open_order"]),
    };

    this->closed_positions.push_back(position);
  }

  this->performance.symbol = this->symbol;
}

#endif
