#ifndef DB__POSITION_net_return
#define DB__POSITION_net_return

#include "deps.cpp"                     // json
#include "get_net_return_positions.cpp" // get_net_return_positions
#include "lib/formatted.cpp"            // Formatted
#include "lib/utils/float.cpp"          // ::utils::float_
#include "lib/utils/integer.cpp"        // ::utils::integer_
#include "lib/utils/io.cpp"             // ::utils::io
#include "position.h" // DB::Position, fmt, net_return_args_t, position_t
#include <iostream>   // std::cout, std::endl
#include <list>       // std::list
#include <math.h>     // INFINITY, abs
#include <stdio.h>    // printf
#include <string>     // std::string
#include <time.h>     // time
#include <utility>    // std::pair

void DB::Position::net_return(const net_return_args_t args) {
  const double timer_start_epoch = time(nullptr);
  const std::string api_key = args.api_key;
  const std::string start_at = args.start_at;
  double net_return_ = 0.0;

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
      .limit = args.limit,
      .start_at = args.start_at,
      .symbol = args.symbol,
  });

  const int total_positions = positions.size();

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
            .debug = args.debug,
            .symbol = args.symbol,
            .timestamp_upper_bound = position.opened_at,
        });

    net_return_ += position.current_profit * abs(position.close_order_quantity);

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
