#ifndef DB__ACCOUNT_STAT_insert
#define DB__ACCOUNT_STAT_insert

#include "account_stat.h" // DB::AccountStat
#include <libpq-fe.h>     // PQescapeLiteral, PQfreemem
#include <stdio.h>        // snprintf
#include <string.h>       // strlen
#include <string>         // std::string, std::to_string

void DB::AccountStat::insert(const insert_args_t args) {
  const double equity = args.equity;
  const double margin_buying_power = args.margin_buying_power;
  const double margin_multiplier = args.margin_multiplier;
  const std::string api_key_id = args.api_key_id;

  const char *query_format = R"(
    insert into account_stats (api_key_id, equity, margin_buying_power, margin_multiplier)
      values (%s, %f, %f, %f)
  )";

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         std::to_string(equity).size() +
                         std::to_string(margin_buying_power).size() +
                         std::to_string(margin_multiplier).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, equity,
           margin_buying_power, margin_multiplier);

  PQfreemem(sanitized_api_key_id);

  this->conn.exec(query);
}

#endif
