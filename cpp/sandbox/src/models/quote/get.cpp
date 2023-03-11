#ifndef DB__QUOTE_get
#define DB__QUOTE_get

#include "lib/utils/string.cpp"     // ::utils::string
#include "lib/utils/vector.cpp"     // ::utils::vector
#include "quote.h"                  // DB::Quote, quote_t, query_result_t
#include "result_to_collection.cpp" // result_to_collection
#include <libpq-fe.h>               // PQescapeLiteral, PQfreemem
#include <math.h>                   // INFINITY
#include <string>                   // std::string, std::stod, std::to_string
#include <vector>                   // std::vector

std::vector<DB::Quote::quote_t> DB::Quote::get(const std::string symbol,
                                               const double limit = INFINITY) {

  char *sanitized_symbol =
      PQescapeLiteral(this->conn.conn, symbol.c_str(), sizeof(symbol.c_str()));

  const std::string limit_clause =
      limit == INFINITY ? "" : " limit " + std::to_string((int)limit);

  std::string query = "select ask, bid, symbol, extract(epoch from timestamp) "
                      "as timestamp from quotes where symbol=" +
                      std::string(sanitized_symbol) + limit_clause;

  query_result_t query_result = this->conn.exec(query);
  PQfreemem(sanitized_symbol);

  std::vector<quote_t> result = result_to_collection(query_result);

  return result;
}

#endif
