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
#include <list>                 // std::list
#include <stdio.h>              // snprintf
#include <string.h>             // strlen
#include <string>               // std::string, std::to_string

std::list<DB::Quote::quote_t> DB::Quote::get_last(get_last_args_t args) {
  const double timestamp_upper_bound = args.timestamp_upper_bound;
  const int limit = args.limit;
  const long int limit_offset = args.limit_offset;
  const std::string symbol = args.symbol;

  const std::string limit_clause =
      limit ? std::string("limit ") + std::to_string(limit) : "";

  const std::string limit_offset_clause =
      limit_offset ? std::string("offset ") + std::to_string(limit_offset) : "";

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), symbol.size());

  const char *query_format = R"(
    select
      ask,
      bid,
      id,
      symbol,
      extract(epoch from timestamp) as timestamp_epoch
    from
      quotes
    where
      symbol = upper(%s)
      and timestamp <= to_timestamp(%f)
    order by
      timestamp desc
    %s
    %s
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_symbol) +
                         std::to_string(timestamp_upper_bound).size() +
                         limit_clause.size() + limit_offset_clause.size();
  ;

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_symbol,
           timestamp_upper_bound, limit_clause.c_str(),
           limit_offset_clause.c_str());

  query_result_t query_result = this->conn.exec(query, args.debug);
  PQfreemem(sanitized_symbol);

  std::list<quote_t> result = result_to_quotes(query_result);

  return result;
}

#endif
