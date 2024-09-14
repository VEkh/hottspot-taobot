#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT_log_daily
#define PERFORMANCE__ACCOUNT_SNAPSHOT_log_daily

#include "account_snapshot.h" // Performance::AccountSnapshot, account_snapshot_t, fmt
#include "deps.cpp"           // json
#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/float.cpp"   // ::utils::float_
#include "lib/utils/integer.cpp" // ::utils::integer_
#include "lib/utils/io.cpp"      // ::utils::io
#include "lib/utils/map.cpp"     // ::utils::map
#include "lib/utils/time.cpp"    // ::utils::time_
#include <iostream>              // std::cout, std::endl
#include <list>                  // std::list
#include <map>                   // std::map
#include <math.h>                // abs
#include <stdio.h>               // printf
#include <string>                // std::stod, std::stoi, std::string
#include <time.h>                // time

void Performance::AccountSnapshot::log_daily() {
  const json config_json =
      ::utils::io::load_config(this->api_name, this->api_key);

  const json api_key_json = config_json[this->api_key];

  std::cout << fmt.bold << fmt.cyan;
  std::cout << "\nEnvironment: " << fmt.yellow << api_key.c_str();
  std::cout << fmt.cyan << std::endl << std::endl;
  puts(api_key_json.dump(2).c_str());
  std::cout << fmt.reset;

  const std::string api_key_id = api_key_json["id"];

  std::list<account_snapshot_t> snapshots =
      this->db_account_stat.get_daily_snapshots({
          .api_key_id = api_key_id,
          .debug = this->debug,
          .end_at = this->end_at,
          .start_at = this->start_at,
      });

  if (snapshots.empty()) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Failed to read snapshots for %s.", api_key_id.c_str());
    std::cout << fmt.reset << std::endl;
    return;
  }

  double daily_dollars = 0.0;
  double daily_ratio = 0.0;
  int day_count = 0;
  int loss_count = 0;
  int win_count = 0;

  for (std::list<account_snapshot_t>::iterator it = snapshots.begin();
       it != snapshots.end(); it++, day_count++) {
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

    loss_count += (int)current_profit < 0;
    win_count += (int)current_profit >= 0;

    Formatted::Stream profit_color = current_profit >= 0 ? fmt.green : fmt.red;

    const std::string snapshot_time =
        ::utils::time_::date_string(snapshot.timestamp, "%A, %B %e %Y", "GMT");

    std::cout << fmt.bold << fmt.cyan << fmt.underline << std::endl;
    std::cout << snapshot_time;
    std::cout << fmt.no_underline << profit_color << std::endl;

    printf("Current Equity:             $%'.2f (%+'.2f) (%+'.2f%%)\n",
           current_equity, current_profit, current_profit_percent);
    printf("Max Equity:                 $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           max_equity, max_profit, max_profit_percent,
           ::utils::time_::date_string(max_equity_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Min Equity:                 $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           min_equity, min_profit, min_profit_percent,
           ::utils::time_::date_string(min_equity_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Original Equity:            $%'.2f\n", original_equity);
  }

  std::cout << fmt.bold << fmt.cyan << fmt.underline << std ::endl;
  std::cout << "📊 Stats\n";
  std::cout << fmt.reset;

  const double avg_daily_dollars = daily_dollars / day_count;
  const double avg_daily_ratio = daily_ratio / day_count;
  const double win_rate_percent = 100 * ((double)win_count / day_count);

  Formatted::Stream avg_daily_dollars_color =
      avg_daily_dollars < 0 ? fmt.red : fmt.green;
  Formatted::Stream avg_daily_ratio_color =
      avg_daily_ratio < 0 ? fmt.red : fmt.green;
  Formatted::Stream total_color = daily_dollars < 0 ? fmt.red : fmt.green;

  std::cout << fmt.bold << avg_daily_dollars_color;
  printf("Avg Daily Return:           %c$%'.2f\n",
         ::utils::float_::sign_char(avg_daily_dollars), abs(avg_daily_dollars));

  std::cout << fmt.bold << avg_daily_ratio_color;
  printf("Avg Daily %% Return:         %+'.2f%%\n", avg_daily_ratio * 100.0);

  std::cout << fmt.bold << total_color;
  printf("Total Return:               %c$%'.2f\n",
         ::utils::float_::sign_char(daily_dollars), abs(daily_dollars));

  printf("Win Rate:                   %'iW (%.2f%%) %'iL (Total: %'i)\n",
         win_count, win_rate_percent, loss_count, day_count);

  std::cout << std::endl;

  const double duration = time(nullptr) - this->timer_start;

  std::cout << fmt.bold << fmt.cyan;
  printf("⌚ Finished in %s\n",
         ::utils::integer_::seconds_to_clock(duration).c_str());
  std::cout << fmt.reset << std::endl;
}

#endif
