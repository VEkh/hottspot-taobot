#ifndef PERFORMANCE__LOGGER_log_daily_snapshots
#define PERFORMANCE__LOGGER_log_daily_snapshots

#include "deps.cpp"              // json
#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/float.cpp"   // ::utils::float_
#include "lib/utils/integer.cpp" // ::utils::integer_
#include "lib/utils/io.cpp"      // ::utils::io
#include "lib/utils/map.cpp"     // ::utils::map
#include "lib/utils/time.cpp"    // ::utils::time_
#include "logger.h"              // Performance::Logger, account_snapshot_t
#include <iostream>              // std::cout, std::endl
#include <list>                  // std::list
#include <locale.h>              // setlocale
#include <map>                   // std::map
#include <math.h>                // abs
#include <stdio.h>               // printf
#include <string>                // std::stod, std::stoi, std::string
#include <time.h>                // time

struct should_increment_stop_profit_reached_count_args_t {
  double max_equity_timestamp;
  double max_profit_percent;
  double min_equity_timestamp;
  double min_profit_percent;
  double stop_loss_percent;
  double stop_profit_percent;
};

bool should_increment_stop_profit_reached_count(
    const should_increment_stop_profit_reached_count_args_t args) {
  const double max_equity_timestamp = args.max_equity_timestamp;
  const double max_profit_percent = args.max_profit_percent;
  const double min_equity_timestamp = args.min_equity_timestamp;
  const double min_profit_percent = args.min_profit_percent;
  const double stop_loss_percent = args.stop_loss_percent;
  const double stop_profit_percent = args.stop_profit_percent;

  if (max_profit_percent < stop_profit_percent) {
    return false;
  }

  if (min_profit_percent > stop_loss_percent) {
    return true;
  }

  return max_equity_timestamp < min_equity_timestamp;
}

void Performance::Logger::log_daily_snapshots(
    std::map<std::string, std::string> args) {
  std::map<std::string, std::string> default_flags = {
      {"debug", "0"},
      {"project", "alpaca"},
      {"stop-loss", "-2.0"},
      {"stop-profit", "2.0"},
  };

  std::map<std::string, std::string> flags =
      ::utils::map::merge(default_flags, args);

  const bool debug = ::utils::io::flag_to_bool("debug", flags["debug"]);
  const double start_epoch = time(nullptr);
  const double stop_loss_percent = std::stod(flags["stop-loss"]);
  const double stop_profit_percent = std::stod(flags["stop-profit"]);
  const std::string api_key = flags["api-key"];

  double daily_dollars = 0.0;
  double daily_ratio = 0.0;
  int day_count = 0;
  int stop_profit_reached_day_count = 0;

  setlocale(LC_NUMERIC, "");
  Formatted::fmt_stream_t fmt = Formatted::stream();

  json config_json = ::utils::io::load_config(flags["project"], api_key);
  json api_key_json = config_json[api_key];

  const std::string api_key_id = api_key_json["id"];

  std::cout << fmt.bold << fmt.cyan;
  std::cout << "\nEnvironment: " << fmt.yellow << api_key.c_str();
  std::cout << fmt.cyan << std::endl << std::endl;
  puts(api_key_json.dump(2).c_str());
  std::cout << fmt.reset;

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
    stop_profit_reached_day_count +=
        (int)(should_increment_stop_profit_reached_count({
            .max_equity_timestamp = max_equity_timestamp,
            .max_profit_percent = max_profit_percent,
            .min_equity_timestamp = min_equity_timestamp,
            .min_profit_percent = min_profit_percent,
            .stop_loss_percent = stop_loss_percent,
            .stop_profit_percent = stop_profit_percent,
        }));

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
  const double stop_profit_reached_percent =
      100.0 * stop_profit_reached_day_count / day_count;
  const double target_stop_profit_reached_percent =
      100.0 / (1 + abs(stop_profit_percent / stop_loss_percent));

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

  std::cout << std::endl;

  std::cout << fmt.bold << fmt.yellow;
  printf("Days %.2f%% Target Reached:  %i/%i (%.2f%% 🎯 %.2f%%)\n",
         stop_profit_percent, stop_profit_reached_day_count, day_count,
         stop_profit_reached_percent, target_stop_profit_reached_percent);
  std::cout << fmt.reset << std::endl;

  const double end_epoch = time(nullptr);

  std::cout << fmt.bold << fmt.cyan;
  printf("⌚ Finished in %s\n",
         ::utils::integer_::seconds_to_clock(end_epoch - start_epoch).c_str());
  std::cout << fmt.reset << std::endl;
}

#endif
