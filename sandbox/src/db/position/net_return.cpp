#ifndef DB__POSITION_net_return
#define DB__POSITION_net_return

#include "deps.cpp"                     // json
#include "get_net_return_positions.cpp" // get_net_return_positions
#include "lib/formatted.cpp"            // Formatted
#include "lib/utils/float.cpp"          // ::utils::float_
#include "lib/utils/integer.cpp"        // ::utils::integer_
#include "lib/utils/io.cpp"             // ::utils::io
#include "lib/utils/time.cpp"           // ::utils::time_
#include "position.h" // DB::Position, fmt, net_return_args_t, position_t
#include <iostream>   // std::cout, std::endl
#include <list>       // std::list
#include <map>        // std::map
#include <math.h>     // INFINITY, abs
#include <stdio.h>    // printf
#include <string>     // std::string
#include <time.h>     // time
#include <utility>    // std::pair

void DB::Position::net_return(const net_return_args_t args) {
  const double timer_start_epoch = time(nullptr);
  const std::string api_key = args.api_key;
  double net_return_ = 0.0;

  std::map<std::string, int> day_positions_count;

  json config_json = ::utils::io::load_config(args.project, api_key);
  json api_key_json = config_json[api_key];

  std::cout << fmt.bold << fmt.cyan;
  std::cout << "\nEnvironment: " << fmt.yellow << api_key.c_str();
  std::cout << fmt.cyan << std::endl << std::endl;
  puts(api_key_json.dump(2).c_str());
  std::cout << fmt.reset;

  DB::Quote db_quote(this->conn);
  const std::string api_key_id = api_key_json["id"];

  const std::list<position_t> positions = get_net_return_positions({
      .api_key_id = api_key_id,
      .debug = args.debug,
      .end_at = args.end_at,
      .limit = args.limit,
      .start_at = args.start_at,
      .symbol = args.symbol,
  });

  const int total_positions = positions.size();

  std::cout << std::endl;

  if (args.log_positions) {
    std::cout << fmt.bold << fmt.magenta;
    printf(
        "Opened At                | Current Profit | Min Profit | Max Profit | "
        "#\n");
    printf("-------------------------------------------------------------------"
           "---------------\n");
  }

  int position_i = 0;

  for (const position_t position : positions) {
    net_return_ += position.current_profit * abs(position.close_order_quantity);

    const std::string date_string = ::utils::time_::date_string(
        position.opened_at, "%F", "America/Chicago");

    day_positions_count[date_string]++;

    position_i++;

    std::cout << fmt.bold << fmt.magenta;

    if (args.log_positions) {
      printf("%s      | %+.2f          | %+.2f      | %+.2f      | %i of %i \n",
             ::utils::time_::date_string(position.opened_at, "%F %R CT",
                                         "America/Chicago")
                 .c_str(),
             position.current_profit, position.max_profit, position.min_profit,
             position_i, total_positions);
      printf("-----------------------------------------------------------------"
             "-----------------\n");
    } else {
      std::cout << "Positions Processed: " << position_i << " of "
                << total_positions << "\r";
    }
  }

  int days_n = 0;
  int single_position_days_n = 0;
  std::map<std::string, int>::iterator day_count;

  for (day_count = day_positions_count.begin();
       day_count != day_positions_count.end(); day_count++) {
    if (day_count->second == 1) {
      single_position_days_n++;
    }

    days_n++;
  }

  if (!args.log_positions) {
    std::cout << std::endl;
  }

  std::cout << std::endl;

  const double single_position_days_percent =
      100.0 * ((float)single_position_days_n / days_n);

  std::cout << fmt.bold << fmt.yellow;
  printf("# Single-Position Days: ");
  std::cout << fmt.bold << fmt.cyan;
  printf("%i of %i (%.2f%%)\n", single_position_days_n, days_n,
         single_position_days_percent);
  std::cout << std::endl;

  std::cout << fmt.bold << fmt.cyan;
  printf("💰 %s ", args.symbol.c_str());

  Formatted::Stream net_return_color = net_return_ >= 0.0 ? fmt.green : fmt.red;

  std::cout << fmt.bold << net_return_color;
  printf("Total Return: %c$%.2f\n", ::utils::float_::sign_char(net_return_),
         abs(net_return_));
  std::cout << fmt.reset << std::endl;

  const double timer_end_epoch = time(nullptr);

  std::cout << fmt.bold << fmt.cyan;
  printf("⌚ Finished in %s\n", ::utils::integer_::seconds_to_clock(
                                   timer_end_epoch - timer_start_epoch)
                                   .c_str());
  std::cout << fmt.reset << std::endl;
}

#endif
