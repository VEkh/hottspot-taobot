#ifndef DB__QUOTE_get_last
#define DB__QUOTE_get_last

/*
 * DB::Quote
 * get_last_args_t
 * quote_t
 * query_result_t
 */
#include "quote.h"

#include "result_to_collection.cpp" // result_to_collection
#include <libpq-fe.h>               // PQescapeLiteral, PQfreemem
#include <string>                   // std::string, std::stod, std::to_string
#include <vector>                   // std::vector

std::vector<DB::Quote::quote_t> DB::Quote::get_last(get_last_args_t args) {
  const bool debug = args.debug;
  const int limit = args.limit;
  const std::string symbol = args.symbol;

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), sizeof(symbol.c_str()));

  const std::string limit_clause = " limit " + std::to_string(limit);

  std::string query =
      "select ask, bid, symbol, extract(epoch from timestamp) "
      "as timestamp from quotes where symbol=" +
      std::string(sanitized_symbol) +
      " and id in (select id from quotes where symbol=" + sanitized_symbol +
      " order by timestamp desc limit " + std::to_string(limit) +
      ") order by timestamp asc";

  query_result_t query_result = this->conn.exec(query, debug);
  PQfreemem(sanitized_symbol);

  std::vector<quote_t> result = result_to_collection(query_result);

  return result;
}

#endif
