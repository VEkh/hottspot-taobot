#ifndef DB__ACCOUNT_STAT_upsert
#define DB__ACCOUNT_STAT_upsert

#include "account_stat.h" // DB::AccountStat
#include <libpq-fe.h>     // PQescapeLiteral, PQfreemem
#include <stdio.h>        // snprintf
#include <string.h>       // strlen
#include <string>         // std::string, std::to_string

void DB::AccountStat::upsert(const upsert_args_t args) {
  const double equity = args.equity;
  const double inserted_at = args.inserted_at;
  const double margin_buying_power = args.margin_buying_power;
  const double margin_multiplier = args.margin_multiplier;
  const std::string api_key_id = args.api_key_id;

  const std::string inserted_at_value =
      inserted_at
          ? std::string("to_timestamp(") + std::to_string(inserted_at) + ")"
          : "now()";

  const char *query_format = R"(
    insert into account_stats(api_key_id, equity, inserted_at, margin_buying_power, margin_multiplier)
      values (%s, %f, %s, %f, %f)
    on conflict (api_key_id, inserted_at)
      do update set equity = excluded.equity;
  )";

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         std::to_string(equity).size() +
                         inserted_at_value.size() +
                         std::to_string(margin_buying_power).size() +
                         std::to_string(margin_multiplier).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, equity,
           inserted_at_value.c_str(), margin_buying_power, margin_multiplier);

  PQfreemem(sanitized_api_key_id);

  this->conn.exec(query, args.debug);
}

#endif
