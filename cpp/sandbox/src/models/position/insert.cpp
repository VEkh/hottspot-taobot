#ifndef DB__POSITION_insert
#define DB__POSITION_insert

#include "position.h" // DB::Position
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::string, std::to_string

void DB::Position::insert(const insert_args_t args) {
  const double close_order_execution_mid = args.close_order_execution_mid;
  const double close_order_quantity = args.close_order_quantity;
  const double closed_at = args.closed_at;
  const double max_profit = args.max_profit;
  const double max_profit_at = args.max_profit_at;
  const double open_order_execution_mid = args.open_order_execution_mid;
  const double open_order_quantity = args.open_order_quantity;
  const double opened_at = args.opened_at;
  const double stop_loss = args.stop_loss;
  const double stop_profit = args.stop_profit;

  const std::string api_key_id = args.api_key_id;
  const std::string close_order_id = args.close_order_id;
  const std::string open_order_id = args.open_order_id;
  const std::string symbol = args.symbol;

  const char *query_format = R"(
    insert into positions(api_key_id, close_order_execution_mid, close_order_id, close_order_quantity, closed_at, max_profit, max_profit_at, open_order_execution_mid, open_order_id, open_order_quantity, opened_at, stop_loss, stop_profit, symbol)
      values (%s, %f, %s, %f, to_timestamp(%f), %f, to_timestamp(%f), %f, %s, %f, to_timestamp(%f), %f, %f, %s)
  )";

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  char *sanitized_close_order_id = PQescapeLiteral(
      this->conn.conn, close_order_id.c_str(), close_order_id.size());

  char *sanitized_open_order_id = PQescapeLiteral(
      this->conn.conn, open_order_id.c_str(), open_order_id.size());

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const size_t query_l =
      strlen(query_format) + strlen(sanitized_api_key_id) +
      std::to_string(close_order_execution_mid).size() +
      strlen(sanitized_close_order_id) +
      std::to_string(close_order_quantity).size() +
      std::to_string(closed_at).size() + std::to_string(max_profit).size() +
      std::to_string(max_profit_at).size() +
      std::to_string(open_order_execution_mid).size() +
      strlen(sanitized_open_order_id) +
      std::to_string(open_order_quantity).size() +
      std::to_string(opened_at).size() + std::to_string(stop_loss).size() +
      std::to_string(stop_profit).size() + strlen(sanitized_symbol);

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id,
           close_order_execution_mid, sanitized_close_order_id,
           close_order_quantity, closed_at, max_profit, max_profit_at,
           open_order_execution_mid, sanitized_open_order_id,
           open_order_quantity, opened_at, stop_loss, stop_profit,
           sanitized_symbol);

  PQfreemem(sanitized_api_key_id);
  PQfreemem(sanitized_close_order_id);
  PQfreemem(sanitized_open_order_id);
  PQfreemem(sanitized_symbol);

  this->conn.exec(query, args.debug);
}

#endif
