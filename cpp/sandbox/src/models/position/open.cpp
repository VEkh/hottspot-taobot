#ifndef DB__POSITION_open
#define DB__POSITION_open

#include "position.h" // DB::Position
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::string, std::to_string

void DB::Position::open(const open_args_t args) {
  const double current_profit = args.current_profit;
  const double max_profit = args.max_profit;
  const double max_profit_at = args.max_profit_at;
  const double open_order_execution_mid = args.open_order_execution_mid;
  const double open_order_quantity = args.open_order_quantity;
  const double stop_loss = args.stop_loss;
  const double stop_profit = args.stop_profit;

  const std::string api_key_id = args.api_key_id;
  const std::string open_order_id = args.open_order_id;
  const std::string symbol = args.symbol;

  const char *query_format = R"(
    insert into positions(api_key_id, current_profit, max_profit, max_profit_at, open_order_execution_mid, open_order_id, open_order_quantity, stop_loss, stop_profit, symbol)
      values (%s, %f, %f, to_timestamp(%f), %f, %s, %f, %f, %f, %s)
    on conflict (api_key_id, open_order_id)
      do update set
        current_profit = excluded.current_profit, max_profit = excluded.max_profit, max_profit_at = excluded.max_profit_at, stop_loss = excluded.stop_loss, stop_profit = excluded.stop_profit;
  )";

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  char *sanitized_open_order_id = PQescapeLiteral(
      this->conn.conn, open_order_id.c_str(), open_order_id.size());

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const size_t query_l =
      strlen(query_format) + strlen(sanitized_api_key_id) +
      std::to_string(current_profit).size() +
      std::to_string(max_profit).size() + std::to_string(max_profit_at).size() +
      std::to_string(open_order_execution_mid).size() +
      strlen(sanitized_open_order_id) +
      std::to_string(open_order_quantity).size() +
      std::to_string(stop_loss).size() + std::to_string(stop_profit).size() +
      strlen(sanitized_symbol);

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, current_profit,
           max_profit, max_profit_at, open_order_execution_mid,
           sanitized_open_order_id, open_order_quantity, stop_loss, stop_profit,
           sanitized_symbol);

  PQfreemem(sanitized_api_key_id);
  PQfreemem(sanitized_open_order_id);
  PQfreemem(sanitized_symbol);

  this->conn.exec(query, args.debug);
}

#endif
