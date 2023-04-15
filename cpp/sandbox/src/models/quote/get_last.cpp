#ifndef DB__QUOTE_get_last
#define DB__QUOTE_get_last

/*
 * DB::Quote
 * get_last_args_t
 * quote_t
 * query_result_t
 */
#include "quote.h"

#include "result_to_quotes.cpp" // result_to_quotes
#include <libpq-fe.h>           // PQescapeLiteral, PQfreemem
#include <stdio.h>              // snprintf
#include <string.h>             // strlen
#include <string>               // std::string, std::to_string
#include <vector>               // std::vector

std::vector<DB::Quote::quote_t> DB::Quote::get_last(get_last_args_t args) {
  const int limit = args.limit;
  const std::string symbol = args.symbol;
  const double timestamp_upper_bound = args.timestamp_upper_bound;

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *query_format = R"(
    select
      ask,
      bid,
      symbol,
      extract(epoch from timestamp) as timestamp_epoch
    from
      quotes
    where
      symbol = %s
      and timestamp <= to_timestamp(%f)
    order by
      timestamp desc
    limit %i
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         std::to_string(timestamp_upper_bound).size() +
                         std::to_string(limit).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol,
           timestamp_upper_bound, limit);

  query_result_t query_result = this->conn.exec(query, args.debug);
  PQfreemem(sanitized_symbol);

  std::vector<quote_t> result = result_to_quotes(query_result);

  return result;
}

#endif