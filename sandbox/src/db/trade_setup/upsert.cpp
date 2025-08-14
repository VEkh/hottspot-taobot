#ifndef DB__TRADE_SETUP_upsert
#define DB__TRADE_SETUP_upsert

#include "trade_setup.h" // DB::TradeSetup, find_or_create_by_args_t
#include <stdio.h>       // snprintf
#include <string.h>      // strlen
#include <string>        // std::to_string

void DB::TradeSetup::upsert(const find_or_create_by_args_t args) {
  const int reverse_percentile_id = args.reverse_percentile_id;
  const int stop_profit_id = args.stop_profit_id;

  const char *query_format = R"(
    insert into trade_setups(reverse_percentile_id, stop_profit_id)
      values (%i, %i)
    on conflict (reverse_percentile_id, stop_profit_id)
      do nothing;
  )";

  const size_t query_l = strlen(query_format) +
                         std::to_string(reverse_percentile_id).size() +
                         std::to_string(stop_profit_id).size();

  char query[query_l];

  snprintf(query, query_l, query_format, reverse_percentile_id, stop_profit_id);

  this->conn.exec(query, args.debug);
}

#endif
