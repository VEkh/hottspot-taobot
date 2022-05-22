#ifndef ALPACA__TAO_BOT_write_performance
#define ALPACA__TAO_BOT_write_performance

/*
 * Alpaca::TaoBot
 * order_t
 * position_t
 */
#include "tao_bot.h"

#include "alpaca/constants.cpp" // Alpaca::constants
#include "deps.cpp"             // json
#include "lib/formatted.cpp"    // Formatted
#include "lib/utils/io.cpp"     // utils::io
#include <list>                 // std::list
#include <stdexcept>            // std::invalid_argument
#include <string>               // std::string

void Alpaca::TaoBot::write_performance() {
  try {
    json (*order_to_json)(order_t &) = [](order_t &order) -> json {
      return {
          {"action", Alpaca::constants::ORDER_ACTIONS[order.action]},
          {"id", order.id},
          {"profit", order.profit},
          {"quantity", order.quantity},
          {"timestamp", order.timestamp},
      };
    };

    const std::string filepath = std::string(APP_DIR) +
                                 "/data/alpaca/performance/" +
                                 std::string(symbol) + ".json";

    json performance_json;

    std::list<json> positions;

    for (position_t position : this->closed_positions) {
      json position_json = {
          {"close_order", order_to_json(position.close_order)},
          {"open_order", order_to_json(position.open_order)},
      };

      positions.push_back(position_json);
    }

    performance_json["current_balance"] = this->performance.current_balance;
    performance_json["current_loss_streak_balance"] =
        this->performance.current_loss_streak_balance;
    performance_json["max_balance"] = this->performance.max_balance;
    performance_json["positions"] = positions;
    performance_json["symbol"] = this->performance.symbol;

    ::utils::io::write_to_file(performance_json.dump(2), filepath.c_str());
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message = Formatted::error_message(
        std::string("ALPACA__TAO_BOT_write_performance") +
        ": Parse error while writing performance.");

    throw(std::invalid_argument(error_message));
  }
}

#endif
