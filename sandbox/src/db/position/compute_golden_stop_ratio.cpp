#ifndef DB__POSITION_compute_golden_stop_ratio
#define DB__POSITION_compute_golden_stop_ratio

#include "deps.cpp"                       // json
#include "get_golden_ratio_positions.cpp" // get
#include "lib/formatted.cpp"              // Formatted
#include "lib/utils/integer.cpp"          // ::utils::integer_
#include "lib/utils/io.cpp"               // ::utils::io
#include "position.h"                     // DB::Position, fmt, position_t
#include <algorithm>                      // std::max, std::min
#include <iostream>                       // std::cout, std::endl
#include <list>                           // std::list
#include <map>                            // std::map
#include <math.h>                         // INFINITY, abs
#include <stdio.h>                        // printf
#include <string>                         // std::string
#include <time.h>                         // time
#include <utility>                        // std::pair

void DB::Position::compute_golden_stop_ratio(
    const compute_golden_ratio_args_t args) {
  const std::string api_key = args.api_key;
  const double start_epoch = time(nullptr);

  json config_json = ::utils::io::load_config(args.project, api_key);
  json api_key_json = config_json[api_key];

  std::cout << fmt.bold << fmt.cyan;
  std::cout << "\nEnvironment: " << fmt.yellow << api_key.c_str();
  std::cout << fmt.cyan << std::endl << std::endl;
  puts(api_key_json.dump(2).c_str());
  std::cout << fmt.reset;

  const std::string api_key_id = api_key_json["id"];

  DB::Quote db_quote(this->conn);

  const std::list<position_t> positions = get_golden_ratio_positions({
      .api_key_id = api_key_id,
      .debug = args.debug,
      .limit = 100, // TODO: Revert to 0
      .symbol = args.symbol,
  });

  const int total_positions = positions.size();

  std::map<std::pair<double, double>, int> ratios = {};
  std::list<double> stop_loss_ratios = {};
  std::list<double> stop_profit_ratios = {};

  for (double i = 0.2; i < 3.1; i += 0.1) {
    stop_profit_ratios.push_back(i);
  }

  for (double i = -60.0; i < -10.0; i += 10.0) {
    stop_loss_ratios.push_back(i);
  }

  for (const double stop_profit_ratio : stop_profit_ratios) {
    for (const double stop_loss_ratio : stop_loss_ratios) {
      std::pair<double, double> key = {stop_profit_ratio, stop_loss_ratio};
      ratios[key] = 0;
    }
  }

  std::map<std::pair<double, double>, int>::iterator ratio_it;

  std::cout << std::endl;

  if (args.log_positions) {
    std::cout << fmt.bold << fmt.magenta;
    printf("Max Profit | Min Profit | Avg One Sec Variance | #\n");
    printf("------------------------------------------------------------\n");
  }

  int position_i = 0;
  for (const position_t position : positions) {
    const avg_one_sec_variances_t avg_one_sec_variances =
        db_quote.get_avg_one_sec_variances({
            .symbol = args.symbol,
            .timestamp_upper_bound = position.opened_at,
            .debug = args.debug,
        });

    for (ratio_it = ratios.begin(); ratio_it != ratios.end(); ratio_it++) {
      const double stop_loss_ratio = ratio_it->first.second;
      const double stop_profit_ratio = ratio_it->first.first;
      const double stop_loss = stop_loss_ratio * avg_one_sec_variances.running;
      const double stop_profit = abs(stop_profit_ratio * stop_loss);

      if (position.max_profit < stop_profit) {
        continue;
      }

      if (position.min_profit > stop_loss ||
          position.max_profit_at < position.min_profit_at) {
        ratio_it->second++;
      }
    }

    position_i++;

    std::cout << fmt.bold << fmt.magenta;

    if (args.log_positions) {
      printf("%.2f       |  %.2f     | %.5f              | %i of %i \n",
             position.max_profit, position.min_profit,
             avg_one_sec_variances.running, position_i, total_positions);
      printf("------------------------------------------------------------\n");
    } else {
      std::cout << "Positions Processed: " << position_i << " of "
                << total_positions << "\r";
    }
  }

  if (!args.log_positions) {
    std::cout << std::endl;
  }

  std::cout << std::endl;

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("🥇 %s Golden Ratio Report: %s\n\n", args.symbol.c_str(),
         api_key_id.c_str());
  std::cout << fmt.no_underline;

  std::cout << fmt.yellow;
  printf("Stop Profit Ratio | Stop Loss Ratio | Performance\n");
  printf("---------------------------------------------------------------------"
         "\n");

  for (ratio_it = ratios.begin(); ratio_it != ratios.end(); ratio_it++) {
    const double count = ratio_it->second;
    const double stop_profit_ratio = ratio_it->first.first;
    const double target_percentage = 100 * (1 / (1 + stop_profit_ratio));
    const double win_percentage = 100.0 * count / total_positions;

    Formatted::Stream row_color = fmt.red;

    if (win_percentage >= target_percentage) {
      row_color = fmt.green;
    } else if (target_percentage - win_percentage < 5.0) {
      row_color = fmt.yellow;
    }

    std::cout << row_color;
    printf("%.2f              | %05.1f           | %i / %i (%.2f%% 🎯 %.2f%%)\n",
           ratio_it->first.first, ratio_it->first.second, (int)count,
           total_positions, win_percentage, target_percentage);

    std::cout << fmt.yellow;
    printf("-------------------------------------------------------------------"
           "--\n");
  }

  std::cout << fmt.reset << std::endl;

  const double end_epoch = time(nullptr);

  std::cout << fmt.bold << fmt.cyan;
  printf("⌚ Finished in %s\n",
         ::utils::integer_::seconds_to_clock(end_epoch - start_epoch).c_str());
  std::cout << fmt.reset;
}

#endif
