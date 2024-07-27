#ifndef DB__ACCOUNT_STAT_get_snapshot_with_computed_equity
#define DB__ACCOUNT_STAT_get_snapshot_with_computed_equity

#include "account_stat.h" // DB::AccountStat, account_snapshot_t, query_result_t
#include "lib/formatted.cpp"              // Formatted
#include "result_to_computed_profits.cpp" // result_to_computed_profits
#include <iostream>                       // std::cout, std::endl
#include <libpq-fe.h>                     // PQescapeLiteral, PQfreemem
#include <regex>                          // std::regex, std::regex_search
#include <stdio.h>                        // snprintf
#include <string.h>                       // strlen
#include <string>                         // std::string, std::to_string

DB::AccountStat::account_snapshot_t
DB::AccountStat::get_snapshot_with_computed_equity(
    const get_snapshot_with_computed_equity_args_t args) {
  account_snapshot_t current_snapshot = args.current_snapshot;
  const double end_at = args.end_at;
  const double start_at = args.start_at;
  const std::string api_key_id = args.api_key_id;

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  const char *query_format = R"(
    select
      coalesce(net.profit, 0.0) as profit
    from (
      select
        api_key_id,
        sum((current_profit * abs(open_order_quantity))) as profit
      from
        positions
        where
          api_key_id = %s
          and opened_at between to_timestamp(%f)
          and to_timestamp(%f)
        group by
          api_key_id) as net
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         std::to_string(start_at).size() +
                         std::to_string(end_at).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, start_at,
           end_at);

  PQfreemem(sanitized_api_key_id);

  const query_result_t result = this->conn.exec(query, args.debug);

  std::list<double> computed_profits = result_to_computed_profits(result);

  if (computed_profits.empty()) {
    if (std::regex_search(result.error_message,
                          std::regex("statement timeout"))) {
      const std::string error_message = Formatted::error_message(
          std::string("DB__ACCOUNT_STAT_get_snapshot_with_computed_equity: No"
                      " compute profits for ") +
          api_key_id);

      std::cout << error_message << std::endl;

      return get_snapshot_with_computed_equity(args);
    } else {
      return current_snapshot;
    }
  }

  const double computed_profit = computed_profits.front();

  current_snapshot.equity = current_snapshot.original_equity + computed_profit;

  return current_snapshot;
}

#endif
