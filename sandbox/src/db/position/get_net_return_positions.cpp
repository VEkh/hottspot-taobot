#ifndef DB__POSITION_get_net_return_positions
#define DB__POSITION_get_net_return_positions

#include "position.h"              // DB::Position
#include "result_to_positions.cpp" // result_to_positions
#include <libpq-fe.h>              // PQescapeLiteral, PQfreemem
#include <list>                    // std::list
#include <stdio.h>                 // snprintf
#include <string.h>                // strlen
#include <string>                  // std::string

std::list<DB::Position::position_t> DB::Position::get_net_return_positions(
    const get_net_return_positions_args_t args) {
  const std::string api_key_id = args.api_key_id;
  const std::string end_at = args.end_at;
  const int limit = args.limit;
  const std::string start_at = args.start_at;
  const std::string symbol = args.symbol;

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const std::string limit_clause =
      limit ? "limit " + std::to_string(limit) : "";

  std::string opened_at_end_clause;
  std::string opened_at_start_clause;

  if (!end_at.empty()) {
    char *sanitized_end_at =
        PQescapeLiteral(this->conn.conn, end_at.c_str(), end_at.size());

    const std::string val = std::string(sanitized_end_at) + "::date";

    opened_at_end_clause = "and opened_at < " + val;

    PQfreemem(sanitized_end_at);
  }

  if (!start_at.empty()) {
    char *sanitized_start_at =
        PQescapeLiteral(this->conn.conn, start_at.c_str(), start_at.size());

    const std::string val = std::string(sanitized_start_at) + "::date";

    opened_at_start_clause = "and opened_at >= " + val;

    PQfreemem(sanitized_start_at);
  }

  const char *query_format = R"(
    select
      close_order_quantity,
      current_profit,
      max_profit,
      extract(epoch from max_profit_at) as max_profit_at,
      min_profit,
      extract(epoch from min_profit_at) as min_profit_at,
      extract(epoch from opened_at) as opened_at,
      symbol
    from
      positions
    where
      api_key_id = %s
      and symbol = %s
      and closed_at is not null
      %s
      %s
    order by
      opened_at asc
    %s;
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         strlen(sanitized_symbol) +
                         opened_at_start_clause.size() +
                         opened_at_end_clause.size() + limit_clause.size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, sanitized_symbol,
           opened_at_start_clause.c_str(), opened_at_end_clause.c_str(),
           limit_clause.c_str());

  PQfreemem(sanitized_api_key_id);
  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, args.debug);

  return result_to_positions(result);
}

#endif
