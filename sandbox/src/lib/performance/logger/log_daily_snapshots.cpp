#ifndef PERFORMANCE__LOGGER_log_daily_snapshots
#define PERFORMANCE__LOGGER_log_daily_snapshots

#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // ::utils::float_
#include "lib/utils/time.cpp"  // ::utils::time_
#include "logger.h"            // Performance::Logger, account_snapshot_t
#include <iostream>            // std::cout, std::endl
#include <list>                // std::list
#include <locale.h>            // setlocale
#include <map>                 // std::map
#include <math.h>              // abs
#include <stdio.h>             // printf
#include <string>              // std::stoi, std::string

void Performance::Logger::log_daily_snapshots(
    const log_daily_snapshots_args_t args) {
  const std::string api_key_id = args.api_key_id;
  std::map<std::string, std::string> flags = args.flags;

  const bool debug = flags["debug"].empty() ? false : std::stoi(flags["debug"]);

  double daily_dollars = 0.0;
  double daily_ratio = 0.0;
  int count = 0;

  setlocale(LC_NUMERIC, "");
  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::list<account_snapshot_t> snapshots =
      this->db_account_stat.get_daily_snapshots({
          .api_key_id = api_key_id,
          .end_at = flags["end-at"],
          .start_at = flags["start-at"],
          .debug = debug,
      });

  if (snapshots.empty()) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Failed to read snapshots for %s.", api_key_id.c_str());
    std::cout << fmt.reset << std::endl;
    return;
  }

  for (std::list<account_snapshot_t>::iterator it = snapshots.begin();
       it != snapshots.end(); it++, count++) {
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

    daily_dollars += current_profit;
    daily_ratio += current_profit / original_equity;

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

  std::cout << fmt.bold << fmt.cyan << fmt.underline << std ::endl;
  std::cout << "📊 Stats\n";
  std::cout << fmt.reset;

  const double avg_daily_dollars = daily_dollars / count;
  const double avg_daily_ratio = daily_ratio / count;

  Formatted::Stream avg_daily_dollars_color =
      avg_daily_dollars < 0 ? fmt.red : fmt.green;
  Formatted::Stream avg_daily_ratio_color =
      avg_daily_ratio < 0 ? fmt.red : fmt.green;
  Formatted::Stream total_color = daily_dollars < 0 ? fmt.red : fmt.green;

  std::cout << fmt.bold << avg_daily_dollars_color;
  printf("Avg Daily Return:        %c$%'.2f\n",
         ::utils::float_::sign_char(avg_daily_dollars), abs(avg_daily_dollars));

  std::cout << fmt.bold << avg_daily_ratio_color;
  printf("Avg Daily %% Return:      %+'.2f%%\n", avg_daily_ratio * 100.0);

  std::cout << fmt.bold << total_color;
  printf("Total Return:            %c$%'.2f\n",
         ::utils::float_::sign_char(daily_dollars), abs(daily_dollars));
  std::cout << fmt.reset << fmt.cyan;
}

#endif
