#ifndef OANDA__TAO_BOT_write_performance
#define OANDA__TAO_BOT_write_performance

/*
 * Oanda::TaoBot
 * order_t
 * position_t
 */
#include "tao_bot.h"

#include "deps.cpp"            // json
#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/io.cpp"    // utils::io
#include "oanda/constants.cpp" // Oanda::constants
#include <list>                // std::list
#include <stdexcept>           // std::invalid_argument

void Oanda::TaoBot::write_performance() {
  try {
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

    performance_json["are_funds_sufficient"] =
        this->performance.are_funds_sufficient;
    performance_json["current_balance"] = this->performance.current_balance;
    performance_json["current_loss_streak_balance"] =
        this->performance.current_loss_streak_balance;
    performance_json["is_position_open"] = this->performance.is_position_open;
    performance_json["max_balance"] = this->performance.max_balance;
    performance_json["positions"] = positions;
    performance_json["symbol"] = this->performance.symbol;

    ::utils::io::write_to_file(performance_json.dump(2), filepath.c_str());
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        std::string("OANDA__TAO_BOT_write_performance") +
        ": Parse error while writing performance.");

    throw(std::invalid_argument(error_message));
  }
}

#endif
