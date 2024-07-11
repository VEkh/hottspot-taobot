#ifndef DB__MARKET_CLOSE_get_symbols_closed_at
#define DB__MARKET_CLOSE_get_symbols_closed_at

#include "market_close.h" // DB::MarketClose, market_close_t, query_result_t
#include "result_to_market_closes.cpp" // result_to_market_closes
#include <libpq-fe.h>                  // PQescapeLiteral, PQfreemem
#include <list>                        // std::list
#include <stdio.h>                     // snprintf
#include <string.h>                    // strlen
#include <string>                      // std::string, std::to_string

std::list<std::string> DB::MarketClose::get_symbols_closed_at(
    const get_symbols_closed_at_args_t args) {
  const double epoch = args.epoch;
  const std::string api_key_id = args.api_key_id;

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  const char *query_format = R"(
    select
      *,
      extract(epoch from closed_at) as closed_at_epoch
    from
      market_closes
    where
      api_key_id = %s
      and closed_at = to_timestamp(%f)
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         std::to_string(epoch).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, epoch);

  PQfreemem(sanitized_api_key_id);

  const query_result_t result = this->conn.exec(query, args.debug);

  const std::list<market_close_t> market_closes =
      result_to_market_closes(result);

  std::list<std::string> out;

  for (const market_close_t market_close : market_closes) {
    out.push_back(market_close.symbol);
  }

  return out;
}

#endif
