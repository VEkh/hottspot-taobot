#ifndef DB__POSITION_close
#define DB__POSITION_close

#include "position.h" // DB::Position
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::string, std::to_string

void DB::Position::close(const close_args_t args) {
  const double close_order_execution_mid = args.close_order_execution_mid;
  const double close_order_quantity = args.close_order_quantity;
  const double closed_at = args.closed_at;
  const double current_profit = args.current_profit;
  const double max_profit = args.max_profit;
  const double max_profit_at = args.max_profit_at;
  const double stop_loss = args.stop_loss;
  const double stop_profit = args.stop_profit;

  const std::string api_key_id = args.api_key_id;
  const std::string close_order_id = args.close_order_id;
  const std::string open_order_id = args.open_order_id;

  const char *query_format = R"(
    update
      positions
    set
      close_order_execution_mid = %f,
      close_order_id = %s,
      close_order_quantity = %f,
      closed_at = to_timestamp(%f),
      current_profit = %f,
      max_profit = %f,
      max_profit_at = to_timestamp(%f),
      stop_loss = %f,
      stop_profit = %f
    where
      api_key_id = %s
      and open_order_id = %s
  )";

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  char *sanitized_close_order_id = PQescapeLiteral(
      this->conn.conn, close_order_id.c_str(), close_order_id.size());

  char *sanitized_open_order_id = PQescapeLiteral(
      this->conn.conn, open_order_id.c_str(), open_order_id.size());

  const size_t query_l =
      strlen(query_format) + std::to_string(close_order_execution_mid).size() +
      strlen(sanitized_close_order_id) +
      std::to_string(close_order_quantity).size() +
      std::to_string(closed_at).size() + std::to_string(current_profit).size() +
      std::to_string(max_profit).size() + std::to_string(max_profit_at).size() +
      std::to_string(stop_loss).size() + std::to_string(stop_profit).size() +
      strlen(sanitized_api_key_id) + strlen(sanitized_open_order_id);

  char query[query_l];

  snprintf(query, query_l, query_format, close_order_execution_mid,
           sanitized_close_order_id, close_order_quantity, closed_at,
           current_profit, max_profit, max_profit_at, stop_loss, stop_profit,
           sanitized_api_key_id, sanitized_open_order_id);

  PQfreemem(sanitized_api_key_id);
  PQfreemem(sanitized_close_order_id);
  PQfreemem(sanitized_open_order_id);

  this->conn.exec(query, args.debug);
}

#endif
