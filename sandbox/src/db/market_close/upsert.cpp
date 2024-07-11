#ifndef DB__MARKET_CLOSE_upsert
#define DB__MARKET_CLOSE_upsert

#include "market_close.h" // DB:MarketClose, upsert_args_t
#include <libpq-fe.h>     // PQescapeLiteral, PQfreemem
#include <stdio.h>        // snprintf
#include <string.h>       // strlen
#include <string>         // std::string, std::to_string

void DB::MarketClose::upsert(const upsert_args_t args) {
  const double closed_at = args.closed_at;
  const std::string api_key_id = args.api_key_id;
  const std::string symbol = args.symbol;

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *query_format = R"(
    insert into market_closes(api_key_id, closed_at, symbol)
      values (%s, to_timestamp(%f), upper(%s))
    on conflict (api_key_id, closed_at, symbol)
      do nothing;
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         std::to_string(closed_at).size() +
                         strlen(sanitized_symbol);

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, closed_at,
           sanitized_symbol);

  PQfreemem(sanitized_api_key_id);
  PQfreemem(sanitized_symbol);

  this->conn.exec(query, args.debug);
}

#endif
