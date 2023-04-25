#ifndef ALPACA__PERFORMANCE_LOGGER_log_daily_snapshots
#define ALPACA__PERFORMANCE_LOGGER_log_daily_snapshots

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "lib/formatted.cpp"        // Formatted
#include "lib/utils/time.cpp"       // ::utils::time_
#include "performance_logger.h" // Alpaca::PerformanceLogger, account_snapshot_t
#include <iostream>             // std::cout, std::endl
#include <list>                 // std::list
#include <locale.h>             // setlocale
#include <stdio.h>              // printf
#include <string>               // std::string

void Alpaca::PerformanceLogger::log_daily_snapshots(const std::string api_key) {
  setlocale(LC_NUMERIC, "");
  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::map<std::string, std::string> api_client_flags = this->conn.flags;
  api_client_flags["api-key"] = api_key;

  Alpaca::Client api_client(api_client_flags);

  std::list<account_snapshot_t> snapshots =
      this->db_account_stat.get_daily_snapshots(api_client.config.api_key_id);

  if (snapshots.empty()) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Failed to read snapshots for %s.", api_key.c_str());
    std::cout << fmt.reset << std::endl;
    return;
  }

  for (std::list<account_snapshot_t>::iterator it = snapshots.begin();
       it != snapshots.end(); it++) {
    const account_snapshot_t snapshot = *it;

    const double current_equity = snapshot.equity;
    const double max_equity = snapshot.max_equity;
    const double max_equity_timestamp = snapshot.max_equity_timestamp;
    const double min_equity = snapshot.min_equity;
    const double min_equity_timestamp = snapshot.min_equity_timestamp;
    const double original_equity = snapshot.original_equity;

    const double current_profit = current_equity - original_equity;
    const double current_profit_percent =
        100 * (current_equity - original_equity) / original_equity;
    const double min_profit = min_equity - original_equity;
    const double min_profit_percent =
        100 * (min_equity - original_equity) / original_equity;
    const double max_profit = max_equity - original_equity;
    const double max_profit_percent =
        100 * (max_equity - original_equity) / original_equity;

    Formatted::Stream profit_color = current_profit >= 0 ? fmt.green : fmt.red;

    const std::string snapshot_time =
        ::utils::time_::date_string(snapshot.timestamp, "%A, %B %e %Y", "GMT");

    std::cout << fmt.bold << fmt.cyan << fmt.underline << std::endl;
    std::cout << snapshot_time;
    std::cout << fmt.no_underline << profit_color << std::endl;

    printf("Current Equity:          $%'.2f (%+'.2f) (%+'.2f%%)\n",
           current_equity, current_profit, current_profit_percent);
    printf("Max Equity:              $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           max_equity, max_profit, max_profit_percent,
           ::utils::time_::date_string(max_equity_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Min Equity:              $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           min_equity, min_profit, min_profit_percent,
           ::utils::time_::date_string(min_equity_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Original Equity:         $%'.2f\n", original_equity);
  }

  std::cout << fmt.reset << fmt.cyan;
}

#endif
