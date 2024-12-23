#ifndef DB__POSITION_get_closed_positions
#define DB__POSITION_get_closed_positions

#include "position.h"              // DB::Position, query_result_t
#include "result_to_positions.cpp" // result_to_positions
#include <libpq-fe.h>              // PQescapeLiteral, PQfreemem
#include <list>                    // std::list
#include <stdio.h>                 // snprintf
#include <string.h>                // strlen
#include <string>                  // std::to_string

std::list<DB::Position::position_t>
DB::Position::get_closed_positions(const get_closed_positions_args_t args) {
  const double market_open_epoch = args.market_open_epoch;
  const std::string api_key_id = args.api_key_id;
  const std::string symbol = args.symbol;

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *query_format = R"(
    select
      *,
      extract(epoch from closed_at) as closed_at_epoch,
      extract(epoch from opened_at) as opened_at_epoch
    from
      positions
    where
      api_key_id = %s
      and symbol = %s
      and closed_at is not null
      and opened_at >= to_timestamp(%f)
    order by
      opened_at asc
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         strlen(sanitized_api_key_id) +
                         std::to_string(market_open_epoch).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, sanitized_symbol,
           market_open_epoch);

  PQfreemem(sanitized_api_key_id);
  PQfreemem(sanitized_symbol);

  const query_result_t result = this->conn.exec(query, args.debug);

  return result_to_positions(result);
}

#endif
