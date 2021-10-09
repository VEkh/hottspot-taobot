#ifndef OANDA__TAO_BOT_write_performance
#define OANDA__TAO_BOT_write_performance

/*
 * Oanda::TaoBot
 * order_t
 * position_t
 */
#include "tao_bot.h"

#include "deps.cpp"            // json
#include "lib/utils/io.cpp"    // utils::io
#include "oanda/constants.cpp" // Oanda::constants
#include <list>                // std::list

void Oanda::TaoBot::write_performance() {
  json (*order_to_json)(order_t &) = [](order_t &order) -> json {
    return {
        {"action", Oanda::constants::ORDER_ACTIONS[order.action]},
        {"id", order.id},
        {"profit", order.profit},
        {"quantity", order.quantity},
        {"timestamp", order.timestamp},
    };
  };

  std::string filepath = std::string(APP_DIR) + "/data/oanda/performance/" +
                         std::string(symbol) + ".json";

  json performance_json;

  std::list<json> positions;

  for (position_t position : this->closed_positions) {
    json position_json = {
        {"close_order", order_to_json(position.close_order)},
        {"close_timestamp", position.close_timestamp},
        {"open_order", order_to_json(position.open_order)},
    };

    positions.push_back(position_json);
  }

  performance_json["current_balance"] = this->performance.current_balance;
  performance_json["max_balance"] = this->performance.max_balance;
  performance_json["positions"] = positions;

  ::utils::io::write_to_file(performance_json.dump(2), filepath.c_str());
}

#endif
