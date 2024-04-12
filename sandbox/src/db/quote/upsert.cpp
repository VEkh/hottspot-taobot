#ifndef DB__QUOTE_upsert
#define DB__QUOTE_upsert

#include "quote.h"    // DB::Quote
#include <libpq-fe.h> // PQescapeLiteral, PQfreemem
#include <list>       // std::list
#include <string>     // std::string
#include <vector>     // std::vector

void DB::Quote::upsert(const quote_t quote) {
  upsert((const std::list<quote_t>){quote});
}

void DB::Quote::upsert(const std::list<quote_t> quotes) {
  std::string query = "insert into quotes(ask, bid, symbol, timestamp) values ";

  for (std::list<quote_t>::const_iterator it = quotes.begin();
       it != quotes.end(); it++) {
    if (it != quotes.begin()) {
      query += ", ";
    }

    char *sanitized_symbol =
        PQescapeLiteral(this->conn.conn, it->symbol.c_str(), it->symbol.size());

    std::vector<std::string> values = {
        std::to_string(it->ask),
        std::to_string(it->bid),
        sanitized_symbol,
        std::string("to_timestamp(") + std::to_string(it->timestamp) + ")",
    };

    query += "(" + ::utils::vector::join(values, ", ") + ")";
    query += R"(
      on conflict (symbol, "timestamp")
        do update set
          ask = excluded.ask, bid = excluded.bid
    )";

    PQfreemem(sanitized_symbol);
  }

  this->conn.exec(query);
}

#endif
