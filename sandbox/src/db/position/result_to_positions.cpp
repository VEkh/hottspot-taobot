#ifndef DB__POSITION_result_to_positions
#define DB__POSITION_result_to_positions

#include "lib/utils/string.cpp" // ::utils::string
#include "position.h"           // DB::Position, position_t, query_result_t
#include <list>                 // std::list
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

std::list<DB::Position::position_t>
DB::Position::result_to_positions(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  std::list<position_t> out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");
    position_t record;

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "close_order_execution_price") {
        record.close_order_execution_price = std::stod(value);
      }

      if (field == "close_order_id") {
        record.close_order_id = value;
      }

      if (field == "close_order_quantity") {
        record.close_order_quantity = std::stod(value);
      }

      if (field == "closed_at" || field == "closed_at_epoch") {
        record.closed_at = std::stod(value);
      }

      if (field == "current_profit") {
        record.current_profit = std::stod(value);
      }

      if (field == "max_profit") {
        record.max_profit = std::stod(value);
      }

      if (field == "max_profit_at") {
        record.max_profit_at = std::stod(value);
      }

      if (field == "min_profit") {
        record.min_profit = std::stod(value);
      }

      if (field == "min_profit_at") {
        record.min_profit_at = std::stod(value);
      }

      if (field == "open_order_execution_price") {
        record.open_order_execution_price = std::stod(value);
      }

      if (field == "open_order_id") {
        record.open_order_id = value;
      }

      if (field == "open_order_quantity") {
        record.open_order_quantity = std::stod(value);
      }

      if (field == "opened_at" || field == "opened_at_epoch") {
        record.opened_at = std::stod(value);
      }

      if (field == "stop_loss") {
        record.stop_loss = std::stod(value);
      }

      if (field == "stop_profit") {
        record.stop_profit = std::stod(value);
      }

      if (field == "symbol") {
        record.symbol = value;
      }
    }

    out.push_back(record);
  }

  return out;
}

#endif
