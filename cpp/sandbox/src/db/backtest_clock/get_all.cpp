#ifndef DB__BACKTEST_CLOCK_get_all
#define DB__BACKTEST_CLOCK_get_all

/*
 * DB::BacktestClock
 * get_all_args_t
 * query_result_t
 */
#include "backtest_clock.h"

#include "result_to_backtest_clocks.cpp" // result_to_backtest_clocks
#include <libpq-fe.h>                    // PQescapeLiteral, PQfreemem
#include <stdio.h>                       // snprintf
#include <string.h>                      // strlen
#include <string>                        // std::string, std::to_string

std::list<DB::BacktestClock::backtest_clock_t>
DB::BacktestClock::get_all(const get_all_args_t args) {
  const double set_to = args.set_to;
  const std::string api_key_id = args.api_key_id;

  char *sanitized_api_key_id =
      PQescapeLiteral(this->conn.conn, api_key_id.c_str(), api_key_id.size());

  const char *query_format = R"(
    select
      api_key_id,
      extract(epoch from set_to) as set_to,
      symbol
    from
      backtest_clocks
    where
      api_key_id = %s
      and set_to = to_timestamp(%f)
  )";

  const size_t query_l = strlen(query_format) + strlen(sanitized_api_key_id) +
                         std::to_string(set_to).size();

  char query[query_l];

  snprintf(query, query_l, query_format, sanitized_api_key_id, set_to);

  PQfreemem(sanitized_api_key_id);

  const query_result_t result = this->conn.exec(query, args.debug);

  return result_to_backtest_clocks(result);
}

#endif
