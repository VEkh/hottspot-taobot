#ifndef DB__ACCOUNT_STAT_get_snapshot_account_stats
#define DB__ACCOUNT_STAT_get_snapshot_account_stats

#include "account_stat.h"              // DB::AccountStat, query_result_t
#include "result_to_account_stats.cpp" // result_to_account_stats
#include <libpq-fe.h>                  // PQescapeLiteral, PQfreemem
#include <list>                        // std::list
#include <stdio.h>                     // snprintf
#include <string.h>                    // strlen
#include <string>                      // std::string, std::to_string

std::list<DB::AccountStat::account_stat_t>
DB::AccountStat::get_snapshot_account_stats(const get_snapshot_args_t args) {
  const double end_at = args.end_at;
  const std::string api_key_id = args.api_key_id;

  double start_at = args.start_at;

  if (args.use_cache && !this->cached_snapshot_stats.empty()) {
    start_at = this->cached_snapshot_stats.back().inserted_at;
  }

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  const std::string end_at_clause =
      end_at ? "and inserted_at <= to_timestamp(" + std::to_string(end_at) + ")"
             : "";

  const char *query_format = R"(
    select
      api_key_id,
      equity,
      extract(epoch from inserted_at) as inserted_at_epoch,
      margin_buying_power
    from
      account_stats
    where
      api_key_id = %s
      and inserted_at >= to_timestamp(%f)
      %s
    order by
      inserted_at asc
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         std::to_string(start_at).size() + end_at_clause.size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, start_at,
           end_at_clause.c_str());

  PQfreemem(sanitized_api_key_id);

  const query_result_t result = this->conn.exec(query, args.debug);

  return result_to_account_stats(result);
}

#endif
