#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf

#include "etrade/constants.cpp" // ETrade::constants
#include "etrade/deps.cpp"      // json
#include "etrade/types.cpp"     // order_t, position_t
#include "etrade/utils.cpp"     // ETrade::utils
#include "lib/formatted.cpp"    // Formatted
#include "lib/utils/io.cpp"     // utils::io
#include <list>                 // std::list
#include <stdexcept>            // std::invalid_argument
#include <time.h>               // time, time_t
#include <vector>               // std::vector

using order_action_t = ETrade::t::order_action_t;
using order_t = ETrade::t::order_t;
using position_t = ETrade::t::position_t;

std::vector<position_t> read_closed_positions() {
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

  const char *symbol = "TSLA";

  std::vector<position_t> closed_positions = {};

  const char *APP_DIR = "/home/vekh/apps/hottspot_capital/cpp/sandbox";
  std::string filepath = std::string(APP_DIR) +
                         "/data/etrade/closed_positions/" +
                         std::string(symbol) + ".json";

  std::ifstream file;

  try {
    file = ::utils::io::read_file(filepath.c_str());
  } catch (std::invalid_argument &) {
    return closed_positions;
  }

  json closed_positions_json;
  file >> closed_positions_json;

  for (json position_json : closed_positions_json) {
    position_t position = {
        .close_order = json_to_order(position_json["close_order"]),
        .close_timestamp = position_json["close_timestamp"],
        .open_order = json_to_order(position_json["open_order"]),
    };

    closed_positions.push_back(position);
  }

  return closed_positions;
}

void write_closed_positions() {
  json (*order_to_json)(order_t &) = [](order_t &order) -> json {
    return {
        {"action", ETrade::constants::ORDER_ACTIONS[order.action]},
        {"id", order.id},
        {"profit", order.profit},
        {"quantity", order.quantity},
        {"timestamp", order.timestamp},
    };
  };

  const char *symbol = "TSLA";
  order_t close_order{.action = order_action_t::BUY_TO_COVER};
  order_t open_order{.action = order_action_t::SELL_SHORT};
  time_t now;
  time(&now);

  position_t closed_position = {
      .close_order = close_order,
      .close_timestamp = (int)now,
      .open_order = open_order,
  };

  std::vector<position_t> closed_positions = {closed_position};

  const char *APP_DIR = "/home/vekh/apps/hottspot_capital/cpp/sandbox";
  std::string filepath = std::string(APP_DIR) +
                         "/data/etrade/closed_positions/" +
                         std::string(symbol) + ".json";

  json closed_positions_json;

  std::list<json> positions;

  for (position_t position : closed_positions) {
    json position_json = {
        {"close_order", order_to_json(close_order)},
        {"close_timestamp", position.close_timestamp},
        {"open_order", order_to_json(open_order)},
    };

    positions.push_back(position_json);
  }

  closed_positions_json = positions;

  ::utils::io::write_to_file(closed_positions_json.dump(2), filepath.c_str());
}

int main() {
  std::vector<position_t> closed_positions = read_closed_positions();
  printf("Read closed_positions. There are %i\n", (int)closed_positions.size());

  write_closed_positions();
  printf("Wrote closed positions\n");
}
