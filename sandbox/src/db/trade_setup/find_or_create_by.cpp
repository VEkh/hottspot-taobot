#ifndef DB__TRADE_SETUP_find_or_create_by
#define DB__TRADE_SETUP_find_or_create_by

#include "result_to_trade_setups.cpp" // result_to_trade_setups
#include "trade_setup.h" // DB::TradeSetup, find_or_create_by_args_t, query_result_t, trade_setup_t
#include "upsert.cpp" // upsert
#include <stdio.h>    // snprintf
#include <string.h>   // strlen
#include <string>     // std::to_string

DB::TradeSetup::trade_setup_t
DB::TradeSetup::find_or_create_by(const find_or_create_by_args_t args) {
  const int reverse_percentile_id = args.reverse_percentile_id;
  const int stop_profit_id = args.stop_profit_id;

  const char *find_query_format = R"(
    select
      *
    from
      trade_setups
    where
      reverse_percentile_id = %i
      and stop_profit_id = %i;
  )";

  const size_t find_query_l = strlen(find_query_format) +
                              std::to_string(reverse_percentile_id).size() +
                              std::to_string(stop_profit_id).size();

  char find_query[find_query_l];

  snprintf(find_query, find_query_l, find_query_format, reverse_percentile_id,
           stop_profit_id);

  query_result_t get_query_result = this->conn.exec(find_query, args.debug);

  if (get_query_result.tuples.empty()) {
    upsert(args);

    return find_or_create_by(args);
  }

  std::list<trade_setup_t> results = result_to_trade_setups(get_query_result);

  return results.front();
}

#endif
